
#include "MainCharacter.h"
#include "BeaverTownDev.h"
#include "Interact.h"
#include "MainGameInstance.h"
#include "EnemyAI.h"
#include "Chest.h"
#include "HealthPickups.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Public/TimerManager.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//Camera settings
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	PlayerCamera->SetupAttachment(CameraBoom);

	OverheadText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	OverheadText->SetupAttachment(GetRootComponent());
	OverheadText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Settings
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	bCanJump = true;
	SetMaxWalkSpeed(WalkSpeed);
	GetCharacterMovement()->bNotifyApex = true;

	OverheadText->SetVisibility(false);
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Rotates character mesh towards the mouse cursor
	RotateToMousePosition(DeltaTime);
	
	//CHecks for falling damage
	FallingDamage();

	//Rotates Overhead text towards camera
	SetTextRotation(OverheadText);

	if (IsThrowing)
	{
		SetIsThrowing(false);
	}
}

//Sets key-bindigs
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveX", this, &AMainCharacter::MoveX);
	InputComponent->BindAxis("MoveY", this, &AMainCharacter::MoveY);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::JumpPressed);
	InputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::JumpReleased);
	InputComponent->BindAction("Melee", IE_Pressed, this, &AMainCharacter::Melee);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);
	InputComponent->BindAction("Interact", IE_Released, this, &AMainCharacter::InteractReleased);
	
}

void AMainCharacter::MoveX(float value)
{
	if (IsPlayerAlive)
	{
		AddMovementInput(FVector::ForwardVector, value);
	}
	
}

void AMainCharacter::MoveY(float value)
{
	if (IsPlayerAlive)
	{
		AddMovementInput(FVector::RightVector, value);
	}
	
}

void AMainCharacter::Melee()
{
	if (IsPlayerAlive)
	{
		if (CanMelee)
		{
			CanMelee = false;
			//Slows character while attacking
			GetCharacterMovement()->MaxWalkSpeed = WalkSpeedWhileAttacking;
			//Delays melee attack
			GetWorld()->GetTimerManager().SetTimer(MeleeTimerHandle, this, &AMainCharacter::MeleeDelayEnd, AttackDelay);

			FHitResult HitResult;

			//Inflict damage
			GetHitResultFromLineTrace(HitResult, MeleeRange);
			if (HitResult.GetActor())
			{
				//Damage enemy
				if (HitResult.GetActor()->IsA(AEnemyAI::StaticClass()))
				{
					AEnemyAI* EnemyAIHit = Cast<AEnemyAI>(HitResult.GetActor());
					EnemyAIHit->SetTakeDamage(MeleeDamage);
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MeleeParticle, GetTransform(), true);
				}
				//Damage interactable objects
				if (HitResult.GetActor()->GetClass()->IsChildOf(AInteract::StaticClass()))
				{
					AInteract* InteractObject = Cast<AInteract>(HitResult.GetActor());

					if (InteractObject->GetCanBeDamaged())
					{
						InteractObject->OpenEvent();
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MeleeParticle, GetTransform(), true);
					}
				}
			}
		}
	}
}

void AMainCharacter::JumpPressed()
{	
	if (IsPlayerAlive)
	{
		bCanJump = false;
		Jump();
	}
}

void AMainCharacter::JumpReleased()
{
	StopJumping();
}

//Start timer when player is falling with negative velocity
void AMainCharacter::FallingDamage()
{
	if (!bFalling && GetCharacterMovement()->IsFalling() && GetVelocity().Z < 0.f)
	{
		bFalling = true;
		bCanTakeFallingDamage = true;
		StartJumpTime = GetWorld()->GetTimeSeconds();
	}
}

//Calculates falling damage when the player lands
void AMainCharacter::Landed(const FHitResult & Hit)
{
	bCanJump = true;
	bFalling = false;
	EndJumpTime = GetWorld()->GetTimeSeconds();
	float SecondsInAir = EndJumpTime - StartJumpTime;
	if (SecondsInAir > 0.7f && GetVelocity().Z < 0.f)
	{
		//The player was 0.7 seconds or more in air
		//and will take falling damage with (time++)^5
		//this will make the falling damage exponential
		SecondsInAir++;
		float HealthLost = FMath::Pow(SecondsInAir, 5.f);
		auto GameInstance = Cast<UMainGameInstance>(GetGameInstance());
		if (GameInstance && bCanTakeFallingDamage)
		{
			//GameInstance keeps track of player stats
			GameInstance->SetDamageTaken(HealthLost);
			bCanTakeFallingDamage = false;
		}
	}
	else
	{
		bCanTakeFallingDamage = false;
	}
}

//The player can interact with interactable objects through linetrace or collision
void AMainCharacter::Interact()
{
	if (IsPlayerAlive)
	{
		bIsInteractActive = true;
		FHitResult HitResult;
		GetHitResultFromLineTrace(HitResult, InteractReach);

		//Opens chest if hit
		if (HitResult.GetActor())
		{
			if (HitResult.GetActor()->GetClass()->IsChildOf(AInteract::StaticClass()))
			{
				AInteract* InteractObject = Cast<AInteract>(HitResult.GetActor());
				ChestRef = Cast<AChest>(InteractObject);

				//For interacting with HealthPickup
				if (HitResult.GetActor()->IsA(AHealthPickups::StaticClass()))
				{
					AHealthPickups* HealthPickup = Cast<AHealthPickups>(HitResult.GetActor());
					if (HealthPickup)
					{
						if (HealthPickup->GetCanHeal())
						{
							auto GameInstance = Cast<UMainGameInstance>(GetGameInstance());
							GameInstance->SetHealthIncrease(HealthPickup->HealTarget());
							HealthPickup->SetHealUsed();
							if (HealthParticle)
							{
								UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HealthParticle, GetTransform(), true);
							}
						}
					}
				}
				//Checks if angle is right
				float PlayerAngle = GetActorRotation().Yaw;
				float MinAngle = InteractObject->GetActorForwardVector().Rotation().Yaw + InteractObject->GetMinOpenAngle();
				float MaxAngle = InteractObject->GetActorForwardVector().Rotation().Yaw + InteractObject->GetMaxOpenAngle();

				//Open/Close the interactable object if the angle is correct
				if (InteractObject->GetOnlyInteractFromAngle())
				{
					if (PlayerAngle > MinAngle && PlayerAngle < MaxAngle)
					{
						if (InteractObject->GetIsOpenEvent())
						{
							InteractObject->CloseEvent();
						}
						else
						{
							InteractObject->OpenEvent();
						}
					}
				}
				//For interacting with destructible objects
				else if (InteractObject->GetCanBeDamaged() == false)
				{
					if (InteractObject->GetIsOpenEvent())
					{
						InteractObject->CloseEvent();
					}
					else
					{

						InteractObject->OpenEvent();
					}
				}
			}
		}
	}
}

void AMainCharacter::InteractReleased()
{
	bIsInteractActive = false;
}

// Find Viewport Center and mouse 2D position, then get rotation vector based on viewport center. 
// Character rotates towards mouse position.
void AMainCharacter::RotateToMousePosition(float DeltaTime)
{
	if (IsPlayerAlive)
	{
		if (!IsPushingObject)
		{
			/// get viewport center
			FVector2D ViewportSize;
			FVector2D  ViewportCenter;
			GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
			ViewportCenter = ViewportSize / 2;

			/// get mouse position
			float X;
			float Y;
			GetWorld()->GetFirstPlayerController()->GetMousePosition(X, Y);
			FVector2D MousePosition = FVector2D(X, Y);

			/// Get rotation vector
			FVector2D MouseDirection = MousePosition - ViewportCenter;
			MouseDirection.Normalize();
			FVector MouseDirection3D = FVector(MouseDirection.X, MouseDirection.Y, 0);

			/// Fixes rotation offset
			FRotator MyRotator = FRotator(0, 90, 0);
			FRotationMatrix MyRotationMatrix(MyRotator);
			FVector RotatedMouseVector = MyRotationMatrix.TransformVector(MouseDirection3D);

			/// Rotates smoothly towards mouse cursor
			FRotator NewRotation = FMath::RInterpConstantTo(GetActorRotation(), RotatedMouseVector.Rotation(), DeltaTime, TurnInterpolationSpeed);
			GetWorld()->GetFirstPlayerController()->SetControlRotation(NewRotation);
		}
	}
}


//Takes HitResult as out parameter (modifies it by reference)
void AMainCharacter::GetHitResultFromLineTrace(FHitResult &HitResult,float Reach)
{
	FVector StartTrace = GetActorLocation();
	FVector EndTrace = StartTrace + (GetActorRotation().Vector() * Reach);
	EndTrace.Z -= 25.f;
	StartTrace.Z -= 25.f;

	// Line trace from character mesh to get World Dynamic object
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		StartTrace,
		EndTrace,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		FCollisionQueryParams(FName(TEXT("")), false, Cast<AActor>(this))
		);
}


void AMainCharacter::SetIsInteractActive(bool Status)
{
	bIsInteractActive = Status;
}

bool AMainCharacter::GetIsInteractActive() const
{
	return bIsInteractActive;
}

void AMainCharacter::SetIsPushingObject(bool IsPushing)
{
	//If true, locks mesh rotation from mouse
	IsPushingObject = IsPushing;
}


void AMainCharacter::SetMaxWalkSpeed(float MovementSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

USoundBase* AMainCharacter::GetHurtSound()
{
	return HurtSound;
}

void AMainCharacter::SetOverheadText()
{
	//Retreived text from chest looted and display if over the player characters head
	LootText = ChestRef->GetLootText();
	OverheadText->SetText(LootText);
	OverheadText->SetVisibility(true);
	IsTextVisible = true;
	SetVisibilityOverheadText();
}

void AMainCharacter::SetTextRotation(UTextRenderComponent* TextRenderComp)
{
	// Rotates text over character, so it will face the camera
	FVector TextLocation = TextRenderComp->GetComponentLocation();
	FVector CameraLocation = PlayerCamera->GetComponentLocation();
	FVector End = CameraLocation - TextLocation;

	FRotator Rotation = FRotationMatrix::MakeFromX(End).Rotator();
	TextRenderComp->SetWorldRotation(FRotator(Rotation.Pitch, Rotation.Yaw, 0));
}

void AMainCharacter::SetVisibilityOverheadText()
{
	if (IsTextVisible)
	{
		IsTextVisible = false;
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMainCharacter::TimerEnd, OverheadTextDespawnTime);
		}	
	}
}

void AMainCharacter::TimerEnd()
{
	OverheadText->SetVisibility(false);

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}

void AMainCharacter::MeleeDelayEnd()
{
	if (GetWorld())
	{
		CanMelee = true;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		GetWorld()->GetTimerManager().ClearTimer(MeleeTimerHandle);
	}
}

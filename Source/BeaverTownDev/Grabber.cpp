
#include "Grabber.h"
#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "ThrowableItems.h"
#include "TorchPickup.h"
#include "PushableObject.h"
#include "ThrowableRock.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Engine/Public/TimerManager.h"
#include "GameFramework/Actor.h"

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	FindInputComponent();
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Sets the object held in front of the player.
	if (PhysicsHandle->GrabbedComponent)
	{
		FVector EndTrace = GetOwner()->GetActorLocation() + (GetOwner()->GetActorRotation().Vector() * Reach);
		EndTrace.Z -= 25.f;
		EndTrace = EndTrace + GetOwner()->GetActorForwardVector().GetSafeNormal() * 30.f;
		PhysicsHandle->SetTargetLocationAndRotation(EndTrace, GetOwner()->GetActorRotation());	
	}
}

void UGrabber::Grab()
{
	auto CharacterCollision = GetOwner()->FindComponentByClass<UCapsuleComponent>();
	TArray<AActor*> OverlappingActors;

	if (CharacterCollision && !IsHeld)
	{
		// Finds grabbable objects that overlaps with player
		CharacterCollision->GetOverlappingActors(OverlappingActors);
		for (AActor* Actor : OverlappingActors)
		{
			if (Actor->GetClass()->IsChildOf(AThrowableItems::StaticClass()))
			{
				ItemToThrow = Cast<AThrowableItems>(Actor);
				Rock = Cast<AThrowableRock>(ItemToThrow);
			}
			if (Actor->IsA(APushableObject::StaticClass()))
			{
				ObjectToPush = Cast<APushableObject>(Actor);
			}
			if (Actor->GetClass()->IsChildOf(ATorchPickup::StaticClass()))
			{
				TorchToHold = Cast<ATorchPickup>(Actor);
				// torch is placed in character socket and not grabbed by physics handle
				// it uses PickUpTorch() function defined in ATorchPickup
				TorchToHold->PickUpTorch();
				IsHeld = true;
				break;
			}
		}

		// If ItemToThrow was found and nothing is already held by the player
		// It will grab a throwable rock
		if (ItemToThrow && !IsHeld)
		{
			// If item can be picked up, set location and rotation. 
			// Turn collision off while held to not collide with character
			IsHeld = true;
			auto ItemToGrab = ItemToThrow->FindComponentByClass<UStaticMeshComponent>();
			FVector ItemLocation = ItemToGrab->GetOwner()->GetActorLocation();
			FRotator ItemRotation = ItemToGrab->GetOwner()->GetActorRotation();
			PhysicsHandle->GrabComponentAtLocationWithRotation(ItemToGrab, NAME_None, ItemLocation, ItemRotation);
			ItemToThrow->SetActorEnableCollision(false);
			
		}

		// If ObjectToPush was found it will grab the object and simulate pulling/pushing
		// Can do this while holding another item
		if (ObjectToPush)
		{
			//If object can be pushed, set location/rotation and set collision to ignore pawn.
			IsHeld = true;
			auto ItemToGrab = ObjectToPush->FindComponentByClass<UStaticMeshComponent>();
			FVector ItemLocation = ItemToGrab->GetOwner()->GetActorLocation();
			FRotator ItemRotation = ItemToGrab->GetOwner()->GetActorRotation();
			//ObjectToPush->SetCollisionIgnorePawn(true);

			// Adjusting character movement speed to simulate pushing/pulling
			AMainCharacter* Char = Cast<AMainCharacter>(GetOwner());
			if (Char)
			{
				Char->SetIsPushingObject(true);
				Char->SetMaxWalkSpeed(250.f);
				PhysicsHandle->GrabComponentAtLocation(ItemToGrab, NAME_None, GetOwner()->GetActorLocation() );
				IsHeld = true;
			}			
		}
	}
}

void UGrabber::Release()
{
	// Release Torch 
	if (IsHeld && TorchToHold)
	{
		TorchToHold->DropTorch();
		TorchToHold = nullptr;
		IsHeld = false;
	}

	// For rest
	if (PhysicsHandle)
	{
		if (ItemToThrow)
		{
			ItemToThrow->SetActorEnableCollision(true);
			ItemToThrow = nullptr;
		}
		if (ObjectToPush)
		{
			ObjectToPush->SetActorEnableCollision(true);
			//ObjectToPush->SetCollisionIgnorePawn(false);
			ObjectToPush = nullptr;
		}
		//Drop the object/item held
		PhysicsHandle->ReleaseComponent();
		IsHeld = false;

		AMainCharacter* Char = Cast<AMainCharacter>(GetOwner());
		if (Char)
		{
			//If item is released, sets movespeed back to default
			Char->SetIsPushingObject(false);
			Char->SetMaxWalkSpeed(Char->GetWalkSpeed());
		}		
	}
}

// Throws objects and resets physics settings, collision channels, etc.
void UGrabber::Throw()
{
	if (PhysicsHandle && IsHeld && !TorchToHold)
	{	
		if (ItemToThrow)
		{
			ItemToThrow->SetActorEnableCollision(true);
			PhysicsHandle->GrabbedComponent->SetSimulatePhysics(true);
			PhysicsHandle->GrabbedComponent->WakeRigidBody(NAME_None);
			PhysicsHandle->GrabbedComponent->AddImpulse(GetOwner()->GetActorForwardVector()*DefaultThrowForce, NAME_None, true);
			ItemToThrow->SetIsThrown(true);
			ItemToThrow->FindComponentByClass<UStaticMeshComponent>()->SetCollisionResponseToChannel(ECC_Pawn,ECR_Block);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UGrabber::RockCollisionTimerEnd, RockCollisionTimer);
			ItemToThrow = nullptr; 
		}
		if (ObjectToPush)
		{
			ObjectToPush->SetActorEnableCollision(true);
			//ObjectToPush->SetCollisionIgnorePawn(false);
			ObjectToPush = nullptr;
		}
		//If item can be thrown, add force before releasing. Else, object is just released
		PhysicsHandle->ReleaseComponent();
		IsHeld = false;
		
		AMainCharacter* Char = Cast<AMainCharacter>(GetOwner());
		if (Char)
		{
			Char->SetIsPushingObject(false);
			Char->SetIsThrowing(true);
			Char->SetMaxWalkSpeed(Char->GetWalkSpeed());
		}
	}
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing PhysicsHandle component"), *GetOwner()->GetName())
	}
}

// Key-bindings to grab/throw/release
void UGrabber::FindInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Interact", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Shoot", IE_Pressed, this, &UGrabber::Release);
		InputComponent->BindAction("Melee", IE_Released, this, &UGrabber::Throw);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing InputComponent"), *GetOwner()->GetName())
	}
}

// Function called by timer
void UGrabber::RockCollisionTimerEnd()
{
	Rock->SetCollisionIgnorePawn();
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}
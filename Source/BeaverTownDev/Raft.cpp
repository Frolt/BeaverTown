// Fill out your copyright notice in the Description page of Project Settings.

#include "Raft.h"
#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "BeaverTownDevGameModeBase.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Public/TimerManager.h"


// Sets default values
ARaft::ARaft()
{
	PrimaryActorTick.bCanEverTick = true;

	RaftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RaftMesh"));
	RaftMesh->SetupAttachment(RootComponent);

	ForwardTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ForwardTrigger"));
	ForwardTrigger->SetCollisionProfileName(FName("OverlapAll"));
	ForwardTrigger->SetGenerateOverlapEvents(true);
	ForwardTrigger->SetupAttachment(RaftMesh);

	BackwardTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BackwardTrigger"));
	BackwardTrigger->SetCollisionProfileName(FName("OverlapAll"));
	BackwardTrigger->SetGenerateOverlapEvents(true);
	BackwardTrigger->SetupAttachment(RaftMesh);

	RightTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("RightTrigger"));
	RightTrigger->SetCollisionProfileName(FName("OverlapAll"));
	RightTrigger->SetGenerateOverlapEvents(true);
	RightTrigger->SetupAttachment(RaftMesh);

	LeftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftTrigger"));
	LeftTrigger->SetCollisionProfileName(FName("OverlapAll"));
	LeftTrigger->SetGenerateOverlapEvents(true);
	LeftTrigger->SetupAttachment(RaftMesh);
	
}

// Called when the game starts or when spawned
void ARaft::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	TargetLocation = GetActorForwardVector();
	GameMode = Cast<ABeaverTownDevGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->SetRaft(this);

	// Raft physics settings
	RaftMesh->SetSimulatePhysics(true);
	RaftMesh->WakeRigidBody();
	RaftMesh->SetEnableGravity(true);
	RaftMesh->SetMassOverrideInKg(FName(""), 100.f, true);
	RaftMesh->SetAngularDamping(1.f);
	RaftMesh->SetLinearDamping(1.f);
	RaftMesh->SetConstraintMode(EDOFMode::XYPlane);

	// Get primitve to apply force
	RaftPrimitive = Cast<UPrimitiveComponent>(GetRootComponent());

}

// Called every frame
void ARaft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Adds Forward Force
	if (bTimerReady && PlayerCharacter->GetIsInteractActive() && ForwardTrigger->IsOverlappingActor(PlayerCharacter) && RightAngleWithDotProduct(FName("Forward")))
	{
		bTimerReady = false;

		if (RaftPrimitive)
		{
			auto ForceApplied = GetActorForwardVector() * RaftMesh->GetMass() * -1.f * Force;
			auto LocationApplied = PlayerCharacter->GetActorLocation();
			RaftPrimitive->AddForceAtLocation(ForceApplied, LocationApplied);
			UE_LOG(LogTemp, Warning, TEXT("Forward Force Added"))
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}
	// Adds Backward Force
	else if (bTimerReady && PlayerCharacter->GetIsInteractActive() && BackwardTrigger->IsOverlappingActor(PlayerCharacter) && RightAngleWithDotProduct(FName("Backward")))
	{
		bTimerReady = false;

		if (RaftPrimitive)
		{
			auto ForceApplied = GetActorForwardVector() * RaftMesh->GetMass() * 1.f * Force;
			auto LocationApplied = PlayerCharacter->GetActorLocation();
			RaftPrimitive->AddForceAtLocation(ForceApplied, LocationApplied);
			UE_LOG(LogTemp, Warning, TEXT("Backward Force Added"))
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}
	// Adds Left Force
	else if (bTimerReady && PlayerCharacter->GetIsInteractActive() && LeftTrigger->IsOverlappingActor(PlayerCharacter) && RightAngleWithDotProduct(FName("Left")))
	{
		bTimerReady = false;

		if (RaftPrimitive)
		{
			auto ForceApplied = GetActorRightVector() * RaftMesh->GetMass() * 1.f * Force;
			auto LocationApplied = PlayerCharacter->GetActorLocation();
			RaftPrimitive->AddForceAtLocation(ForceApplied, LocationApplied);
			UE_LOG(LogTemp, Warning, TEXT("Left Force Added"))
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}
	// Adds Right Force
	else if (bTimerReady && PlayerCharacter->GetIsInteractActive() && RightTrigger->IsOverlappingActor(PlayerCharacter) && RightAngleWithDotProduct(FName("Right")))
	{
		bTimerReady = false;

		if (RaftPrimitive)
		{
			auto ForceApplied = GetActorRightVector() * RaftMesh->GetMass() * -1.f * Force;
			auto LocationApplied = PlayerCharacter->GetActorLocation();
			RaftPrimitive->AddForceAtLocation(ForceApplied, LocationApplied);
			UE_LOG(LogTemp, Warning, TEXT("Right Force Added"))
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}
}

// Returns true if the Player has the correct angle to interact with raft
// Returns the result from the "DotProductTest" function
bool ARaft::RightAngleWithDotProduct(FName Name)
{
	FVector PlayerVector = PlayerCharacter->GetActorForwardVector().GetSafeNormal();
	FVector RaftVector;

	if (Name == "Forward")
	{
		RaftVector = GetActorForwardVector().GetSafeNormal();
		return DotProductTest(RaftVector, PlayerVector);
	}
	else if (Name == "Backward")
	{
		RaftVector = GetActorForwardVector().GetSafeNormal() * -1.f;
		return DotProductTest(RaftVector, PlayerVector);
	}
	else if (Name == "Left")
	{
		RaftVector = GetActorRightVector().GetSafeNormal() * -1.f;
		return DotProductTest(RaftVector, PlayerVector);
	}
	else if (Name == "Right")
	{
		RaftVector = GetActorRightVector().GetSafeNormal();
		return DotProductTest(RaftVector, PlayerVector);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Player Angle"))
	}
	return false;
}

// Finds out via dotproduct if the player angle is correct with the accepted angle
bool ARaft::DotProductTest(FVector Vector1, FVector Vector2)
{
	float DotProduct = FVector::DotProduct(Vector1, Vector2);
	float DegreeBetweenVectors = FMath::Abs(FMath::RadiansToDegrees(FMath::Acos(DotProduct)));
	if (DegreeBetweenVectors < AcceptedAngle)
	{
		return true;
	}
	return false;
}

// This timer controls how fast the player can interact with the raft
void ARaft::ResetTimer()
{
	bTimerReady = true;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}
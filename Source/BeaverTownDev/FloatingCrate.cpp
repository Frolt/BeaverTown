// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatingCrate.h"
#include "BeaverTownDev.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AFloatingCrate::AFloatingCrate()
{
	PrimaryActorTick.bCanEverTick = true;

	FloatingCrateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	FloatingCrateMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFloatingCrate::BeginPlay()
{
	Super::BeginPlay();
	
	// Physics settings
	FloatingCrateMesh->SetSimulatePhysics(true);
	FloatingCrateMesh->WakeRigidBody();
	FloatingCrateMesh->SetEnableGravity(true);
	FloatingCrateMesh->SetAngularDamping(1.f);
	FloatingCrateMesh->SetLinearDamping(1.f);
	FloatingCrateMesh->SetMassOverrideInKg(FName(""), 100.f, true);
	FloatingCrateMesh->SetConstraintMode(EDOFMode::XYPlane);

	FloatingCratePrimitive = Cast<UPrimitiveComponent>(GetRootComponent());
}

void AFloatingCrate::MoveCrate(FVector Direction)
{
	FVector ForceApplied = Direction * FloatingCrateMesh->GetMass() * Force;
	FVector Location = FloatingCrateMesh->GetSocketLocation(FName("SpawnLocation"));

	if (FloatingCratePrimitive)
	{
		FloatingCratePrimitive->AddForceAtLocation(ForceApplied, Location);
	}
	
}

void AFloatingCrate::MakeFall()
{
	FloatingCrateMesh->SetConstraintMode(EDOFMode::YZPlane);
}

void AFloatingCrate::StopFall()
{
	FloatingCrateMesh->SetConstraintMode(EDOFMode::XYPlane);
}

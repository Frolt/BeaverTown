// Fill out your copyright notice in the Description page of Project Settings.

#include "TorchPickup.h"
#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/SkeletalMeshComponent.h"

ATorchPickup::ATorchPickup()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATorchPickup::BeginPlay()
{
	Super::BeginPlay();

	CharRef = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

// Sets the torch location in character right hand socket
void ATorchPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsHeld)
	{
		SetActorLocation(CharRef->GetMesh()->GetSocketLocation(FName("hand_r")));
		SetActorRotation(FRotator(0.f, CharRef->GetActorRotation().Yaw - 45.f, 20.f));
	}
}

void ATorchPickup::Initialize(UStaticMeshComponent* MeshToSet)
{
	MeshRef = MeshToSet;
}

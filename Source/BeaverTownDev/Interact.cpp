// Fill out your copyright notice in the Description page of Project Settings.

#include "Interact.h"
#include "BeaverTownDev.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInteract::AInteract()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Tick is DISABLED.

	MainRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Main Root"));
	RootComponent = MainRoot;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

}

void AInteract::OpenEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling base class OpenEvent"))
}

void AInteract::CloseEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling base class CloseEvent"))
}

bool AInteract::GetIsOpenEvent()
{
	return bIsOpenEvent;
}

bool AInteract::GetOnlyInteractFromAngle()
{
	return bOnlyInteractFromAngle;
}

float AInteract::GetMaxOpenAngle()
{
	return MaxOpenAngle;
}

float AInteract::GetMinOpenAngle()
{
	return MinOpenAngle;
}

bool AInteract::GetCanBeDamaged()
{
	return bCanBeDamaged;
}

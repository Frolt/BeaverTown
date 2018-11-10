// Fill out your copyright notice in the Description page of Project Settings.

#include "PushableObject.h"
#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APushableObject::APushableObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APushableObject::BeginPlay()
{
	Super::BeginPlay();
	Mesh = FindComponentByClass<UStaticMeshComponent>();
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
}

void APushableObject::SetCollisionIgnorePawn(bool CanIgnore)
{
	if (CanIgnore)
	{
		Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	}
	else
	{
		Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	}	
}
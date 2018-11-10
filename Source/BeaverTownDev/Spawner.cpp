// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"
#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"


ASpawner::ASpawner()
{

	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
}

void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Spawns in random range if enabled
	if (bRandomRange)
	{
		SpawnLocation = GetActorLocation() + (GetActorForwardVector() * FMath::FRandRange(MinX, MaxX));
	}
	else
	{
		SpawnLocation = GetActorLocation();
	}

	// Spawns in intervals and delays first spawn if enabled
	if (bCanSpawn && GetWorld()->GetTimeSeconds() > StartTimeDelay)
	{
		ActorsSpawned++;
		if (bLimitSpawning)
		{
			if (ActorsSpawned >= SpawnLimit)
			{
				bCanSpawn = false;
				return;
			}
		}
		bCanSpawn = false;
		
		// Spawns object and adds the chosen LifeSpan to the object
		if (ObjectToSpawn)
		{
			SpawnRotation = GetActorRotation();
			SpawnedActor = GetWorld()->SpawnActor<AActor>(ObjectToSpawn, SpawnLocation, SpawnRotation);
			SpawnedActor->SetLifeSpan(TimeUntilDestruction);
		}
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpawner::ResetTimer, Time, false);
	}
}

void ASpawner::ResetTimer()
{
	bCanSpawn = true;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

/*
This class can spawn objects in the world with different settings
The different settings allow it to take care of almost all the object spawning in the game.
*/

UCLASS()
class BEAVERTOWNDEV_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawner();

public:	
	virtual void Tick(float DeltaTime) override;

	void ResetTimer();

private:
	// Spawner settings
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		float Time = 5.f;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		float TimeUntilDestruction = 10.f;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		float StartTimeDelay = 0.f;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		bool bRandomRange = false;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		float MaxX = 50.f;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		float MinX = -50.f;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		UClass* ObjectToSpawn = nullptr;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		bool bLimitSpawning = false;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		int SpawnLimit = 1;
	
	AActor *SpawnedActor = nullptr;
	FVector SpawnLocation;
	FRotator SpawnRotation;
	bool bCanSpawn = true;
	FTimerHandle TimerHandle;
	int ActorsSpawned = 0;
	
	
};

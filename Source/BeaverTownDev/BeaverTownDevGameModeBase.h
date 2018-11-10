// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BeaverTownDevGameModeBase.generated.h"

/*
Keeps track of pointer references with setters and getters
*/

// Forward declarations
class ARaft;
class ARollingDoor;

UCLASS()
class BEAVERTOWNDEV_API ABeaverTownDevGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	ARaft* Raft = nullptr;
	ARollingDoor* Door = nullptr;

public:
	void SetRaft(ARaft* RaftToSet);
	void SetDoor(ARollingDoor* DoorToSet);
	UFUNCTION(BlueprintCallable, Category = "Getter")
		ARollingDoor* GetDoor();
	UFUNCTION(BlueprintCallable, Category = "Getter")
		ARaft* GetRaft();

};

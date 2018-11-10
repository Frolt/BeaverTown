// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"

/*
A class that spawns an object when the player overlaps with the trigger volume
*/
class ATriggerVolume;
UCLASS()
class BEAVERTOWNDEV_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrap();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Trap")
		USoundBase* TriggerSound;
	UPROPERTY(EditAnywhere,Category = "Trap")
		ATriggerVolume* TrapTrigger = nullptr;
	UPROPERTY(EditAnywhere, Category = "Trap")
		UClass* ObjectToSpawn = nullptr;
	UPROPERTY(EditAnywhere, Category = "Trap")
		float Lifetime = 0;

	bool TrapActive = true;
	void TrapTriggered();
	
};

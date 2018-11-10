// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact.h"
#include "DestructibleRock.generated.h"

/*
Rock that can be broken with player melee attack
Rock spawns smaller throwable rocks in a random pattern when destroyed.
*/

UCLASS()
class BEAVERTOWNDEV_API ADestructibleRock : public AInteract
{
	GENERATED_BODY()
	
public:
	ADestructibleRock();

	virtual void OpenEvent() override;

	UPROPERTY(EditAnywhere, Category = "Rock")
		int32 Health = 100;
	UPROPERTY(EditAnywhere, Category = "Rock")
		int32 Damage = 25;
	UFUNCTION(BlueprintImplementableEvent, Category = "Rock")
		void PlayRockHitSound();
	UFUNCTION(BlueprintImplementableEvent, Category = "Rock")
		void BreakRock();
	UPROPERTY(EditAnywhere)
		class UParticleSystem* DestroyParticle = nullptr;
};

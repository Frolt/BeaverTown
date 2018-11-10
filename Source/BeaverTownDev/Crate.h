// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact.h"
#include "Crate.generated.h"

/*
Destructable crate that spawns a random crystal when destroyed
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCrateTriggerEvent);

UCLASS()
class BEAVERTOWNDEV_API ACrate : public AInteract
{
	GENERATED_BODY()
	
	
public:
	ACrate();

	virtual void OpenEvent() override;
	UFUNCTION(BlueprintCallable, Category = Crate)
		bool GetIsBroken();
	UPROPERTY(BlueprintAssignable)
		FCrateTriggerEvent CrateOpen;
	UPROPERTY(BlueprintReadWrite)
		int32 RandomSpawn = 0;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* DestroyParticle = nullptr;

private:
	UPROPERTY(EditAnywhere)
		int32 Health = 100;
	bool bIsBroken = false;
	

};

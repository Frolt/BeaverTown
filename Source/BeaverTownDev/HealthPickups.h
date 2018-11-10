// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact.h"
#include "HealthPickups.generated.h"

/**
 * Objects that can be placed in the world. When the player interacts with them, he will receive healing.	
 * Can only be used once
 */
UCLASS()
class BEAVERTOWNDEV_API AHealthPickups : public AInteract
{
	GENERATED_BODY()

public:
	AHealthPickups();

	float HealTarget();

	UFUNCTION(BlueprintCallable, Category = "HealingPickup")
		bool GetCanHeal() const { return CanHeal; }

	void SetHealUsed() { CanHeal = false; }

	
protected:
		virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere,Category="Healing")
		float HealingApplied = 40.f;
	bool CanHeal = true;
		
};

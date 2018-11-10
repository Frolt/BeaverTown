// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact.h"
#include "Lever.generated.h"

/*
A lever that can trigger an event when interacted with
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLeverTriggerEvent);

// Forward declarations
class APickup;
class AChest;

UCLASS()
class BEAVERTOWNDEV_API ALever : public AInteract
{
	GENERATED_BODY()
	
public:
	ALever();

	virtual void OpenEvent() override;
	virtual void CloseEvent() override;

	UPROPERTY(BlueprintAssignable)
		FLeverTriggerEvent LeverOpen;
	UPROPERTY(BlueprintAssignable)
		FLeverTriggerEvent LeverClose;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowableItems.generated.h"

/*
Base class for all other throwable items
Contains some basic settings for throwable items
(We only have one throwable item that is "ThrowableRock")
*/

UCLASS()
class BEAVERTOWNDEV_API AThrowableItems : public AActor
{
	GENERATED_BODY()
	
public:	
	AThrowableItems();
	void SetIsThrown(bool IsThrow);
	UFUNCTION()
		bool GetIsThrown() const { return IsThrown; }

private:
	bool IsThrown = false;

};

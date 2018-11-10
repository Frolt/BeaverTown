// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BurnableObjects.generated.h"

/*
All objects that can be set on fire derives from this class
The "IgniteBurnableObjects" function allows the fire to spread between 
different burnable types. (the log can ignite sawtable etc)
This function uses polymorphism principles with blueprint.
*/

UCLASS()
class BEAVERTOWNDEV_API ABurnableObjects : public AActor
{
	GENERATED_BODY()
	
public:	
	ABurnableObjects();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "FIRE")
		bool bIsLit = false;
	UPROPERTY(BlueprintReadWrite, Category = "FIRE")
		bool bCanSpread = false;

public:	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "FIRE")
		void IgniteBurnableObjects();
	
};

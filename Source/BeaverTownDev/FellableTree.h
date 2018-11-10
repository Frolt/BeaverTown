// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact.h"
#include "FellableTree.generated.h"

/*
Tree that can be knocked over by players melee attack.
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFellTree);

UCLASS()
class BEAVERTOWNDEV_API AFellableTree : public AInteract
{
	GENERATED_BODY()

public:
	AFellableTree();

	virtual void OpenEvent() override;

	UPROPERTY(BlueprintAssignable, Category = "Tree")
		FFellTree TreeOpen;
	UPROPERTY(EditAnywhere, Category = "Tree")
		int32 Health = 100;
	UFUNCTION(BlueprintImplementableEvent, Category = "Tree")
		void PlayChopSound();

private:
	bool bCanFall = true;
};

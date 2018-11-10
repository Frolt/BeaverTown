// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interact.generated.h"

/*
This works as a baseclass and provides the common/basic functionality
to all the interactable objects.
*/

UCLASS()
class BEAVERTOWNDEV_API AInteract : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteract();

public:	
	// These two functions are overridden in most of the derived classes
	virtual void OpenEvent();
	virtual void CloseEvent();
	// Getters
	bool GetIsOpenEvent();
	bool GetOnlyInteractFromAngle();
	bool GetCanBeDamaged();
	float GetMaxOpenAngle();
	float GetMinOpenAngle();

protected:
	// Settings
	UPROPERTY(BlueprintReadWrite)
		bool bIsOpenEvent = false;
	UPROPERTY(BlueprintReadWrite)
		bool bOnlyInteractFromAngle = false;
	UPROPERTY(EditAnywhere)
		float MaxOpenAngle = 0;
	UPROPERTY(EditAnywhere)
		float MinOpenAngle = 0;
	bool bCanBeDamaged = false;

private:
	UPROPERTY(EditAnywhere)
		USceneComponent * MainRoot = nullptr;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent * BaseMesh = nullptr;

	
};

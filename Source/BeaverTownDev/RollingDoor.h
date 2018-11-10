// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollingDoor.generated.h"

/*
A Rolling stone door that can only be opened by a lever or igniting torches
Most of the functionality and animation is in the derived blueprint
*/

class ATorchStatic;

UCLASS()
class BEAVERTOWNDEV_API ARollingDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARollingDoor();

protected:
	virtual void BeginPlay() override;

public:	
	// Open/Close functions
	UFUNCTION(BlueprintImplementableEvent, Category = "RollingDoor")
		void OpenDoor();
	UFUNCTION(BlueprintImplementableEvent, Category = "RollingDoor")
		void CloseDoor();

	// Torch references to open the door
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ATorchStatic* Torch1 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ATorchStatic* Torch2 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ATorchStatic* Torch3 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ATorchStatic* Torch4 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ATorchStatic* Torch5 = nullptr;

};

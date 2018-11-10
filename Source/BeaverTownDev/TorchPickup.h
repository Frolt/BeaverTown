// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TorchPickup.generated.h"

/*
Torch/Stick that player can pickup
All the light functionality is in blueprint
*/

// Forward declaration
class AMainCharacter;

UCLASS()
class BEAVERTOWNDEV_API ATorchPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ATorchPickup();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
		bool IsHeld = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsLit;
	UFUNCTION(BlueprintImplementableEvent, Category = "Torch")
		void PickUpTorch();
	UFUNCTION(BlueprintImplementableEvent, Category = "Torch")
		void DropTorch();

private:
	UStaticMeshComponent* MeshRef = nullptr;
	AMainCharacter* CharRef = nullptr;

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Torch")
		void Initialize(UStaticMeshComponent* MeshToSet);

};

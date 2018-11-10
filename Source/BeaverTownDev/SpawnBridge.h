// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnBridge.generated.h"
/*
	Sets objects visible depending on how many items the player has looted.
	Creates a full bridge when the player has collected all of the parts
*/

class ATriggerVolume;

UCLASS()
class BEAVERTOWNDEV_API ASpawnBridge : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASpawnBridge();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* BridgeTrigger = nullptr;

	UPROPERTY(EditAnywhere)
		int32 BridgeIndex = 0;

	UPROPERTY(EditAnywhere)
		int32 PlayerCollectedWood;
protected:

	virtual void BeginPlay() override;

private:

	UStaticMeshComponent* BridgeMesh = nullptr;
	void BuildBridge();

	
	
};

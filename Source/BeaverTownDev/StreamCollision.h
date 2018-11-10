// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StreamCollision.generated.h"

/*
Stream Collision that push AFloatingCrate along the stream direction
Can also make crates fall or stop falling
*/

class UBoxComponent;
class AFloatingCrate;
class UArrowComponent;

UCLASS()
class BEAVERTOWNDEV_API AStreamCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	AStreamCollision();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* StreamRoot = nullptr;
	UPROPERTY(EditAnywhere)
		UBoxComponent* StreamCollision = nullptr;
	UPROPERTY(EditAnywhere)
		UArrowComponent* StreamArrow = nullptr;
	UPROPERTY(EditAnywhere)
		bool bMakeFall = false;
	UPROPERTY(EditAnywhere)
		bool bStopFall = false;

private:
	UBoxComponent* Collision = nullptr;
	AFloatingCrate* Crate = nullptr;
	
};

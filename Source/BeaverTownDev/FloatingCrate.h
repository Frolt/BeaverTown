// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "FloatingCrate.generated.h"

/*
Crate is constrained to simulate floating
Crate is pushed by AStream class in the streams direction
Crate removes constraints and start falling when overlapping with "waterfall" stream
*/

UCLASS()
class BEAVERTOWNDEV_API AFloatingCrate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingCrate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Crate Movement functions
	void MoveCrate(FVector Direction);
	void MakeFall();
	void StopFall();

	UPROPERTY(EditAnywhere, Category = "Floating Crate Settings")
		USceneComponent* FloatingCrateRoot = nullptr;
	UPROPERTY(EditAnywhere, Category = "Floating Crate Settings")
		UStaticMeshComponent* FloatingCrateMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Floating Crate Settings")
		UArrowComponent* FloatingCrateArrow = nullptr;
	UPROPERTY(EditAnywhere, Category = "Floating Crate Settings")
		float Force = 150.f;

	UPrimitiveComponent* FloatingCratePrimitive = nullptr;
	
};

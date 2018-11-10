// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThrowableItems.h"
#include "ThrowableRock.generated.h"

/*
A rock that the player can throw to solve puzzles or inflict damage
*/

UCLASS()
class BEAVERTOWNDEV_API AThrowableRock : public AThrowableItems
{
	GENERATED_BODY()
	
private:

	virtual void BeginPlay() override;
	bool IsThrown = false;
	
public:
	AThrowableRock();
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void SetCollisionIgnorePawn();
	UPROPERTY(EditDefaultsOnly, Category = "Hitbox")
		UStaticMeshComponent* RockMesh = nullptr;
	UPROPERTY(EditAnywhere)
		float RockDamage = 50.f;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

/*
Makes objects that is destroyed/picked up when the player overlaps with them.
All pickable objects will heal the player for 10 hp.
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlaySoundEvent);

// Forward declaration
class AMainCharacter;
class UShapeComponent;

UCLASS()
class BEAVERTOWNDEV_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	APickup();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UPROPERTY(BlueprintAssignable)
		FPlaySoundEvent PlaySoundWhenPickup;

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* PickupRoot;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PickupMesh;
	UPROPERTY(EditAnywhere)
		UShapeComponent* PickupBox;
	AMainCharacter* CharacterPickup = nullptr;
		UPROPERTY(EditAnywhere)
	UParticleSystem* HealthParticle = nullptr;
	
	
};

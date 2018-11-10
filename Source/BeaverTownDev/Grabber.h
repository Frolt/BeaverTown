// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

/*
Component added to AMainCharacter.
Gives the player the ability to grab, throw and release objects
*/

// Forward declarations
class AThrowableItems;
class APushableObject;
class ATorchPickup;
class AThrowableRock;
class UPhysicsHandleComponent;
class UInputComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEAVERTOWNDEV_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGrabber();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	// Pointers to grabbable objects
	UPrimitiveComponent* ComponentToGrab = nullptr;
	AThrowableItems *ItemToThrow = nullptr;
	APushableObject* ObjectToPush = nullptr;
	ATorchPickup* TorchToHold = nullptr;
	FTimerHandle TimerHandle;
	AThrowableRock* Rock = nullptr;

	// Settings variables
	bool StartThrow = false;
	float DefaultThrowForce = 2000;
	float Reach = 30.f;
	bool IsHeld = false;
	UPROPERTY(EditAnywhere)
		float RockCollisionTimer = 3.f;


	UInputComponent* InputComponent = nullptr;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	// Member functions
	void Grab();
	void Release();
	void Throw();
	void FindPhysicsHandle();
	void FindInputComponent();
	void RockCollisionTimerEnd();
};

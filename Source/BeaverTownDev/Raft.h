// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Raft.generated.h"

/*
A raft that can be controlled by the player.
The raft will add force if the player interact with the raft edges at the right angle.
This will simulate paddling
*/

// Forward declarations
class AMainCharacter;
class ABeaverTownDevGameModeBase;
class UBoxComponent;

UCLASS()
class BEAVERTOWNDEV_API ARaft : public AActor
{
	GENERATED_BODY()
	
public:	
	ARaft();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	//TODO
	UFUNCTION(BlueprintImplementableEvent, Category = "Raft")
		void PlaySplashSound();
	void ResetTimer();
	bool RightAngleWithDotProduct(FName Name);
	bool DotProductTest(FVector Vector1, FVector Vector2);

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* RaftRoot;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* RaftMesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* ForwardTrigger;
	UPROPERTY(EditAnywhere)
		UBoxComponent* BackwardTrigger;
	UPROPERTY(EditAnywhere)
		UBoxComponent* RightTrigger;
	UPROPERTY(EditAnywhere)
		UBoxComponent* LeftTrigger;

	// Pointer references
	AMainCharacter* PlayerCharacter = nullptr;
	ABeaverTownDevGameModeBase* GameMode = nullptr;
	UPrimitiveComponent* RaftPrimitive = nullptr;

	// variables
	bool bTimerReady = true;
	FTimerHandle TimerHandle;
	FVector TargetLocation;
	FVector CurrentLocation;
	FHitResult RaftHitResult;

	// Settings variables
	UPROPERTY(EditAnywhere, Category = "Raft Settings")
		float AcceptedAngle = 90.f;
	UPROPERTY(EditAnywhere, Category = "Raft Settings")
		float Timer = .3f;
	UPROPERTY(EditAnywhere, Category = "Raft Settings")
		float Speed = 500.f;
	UPROPERTY(EditAnywhere, Category = "Raft Settings")
		float Force = 2500.f;

};

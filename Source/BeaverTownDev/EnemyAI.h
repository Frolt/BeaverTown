// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyAI.generated.h"


class UBehaviorTree;
class AEnemyAIController;
class AMainCharacter;
class USphereComponent;

UCLASS()
class BEAVERTOWNDEV_API AEnemyAI : public ACharacter
{
	GENERATED_BODY()

public:
	
	AEnemyAI();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "AI")
		UBehaviorTree* BehaviorTree;

protected:
	
	virtual void BeginPlay() override;

private:
	
	//Despawn timer after death
	UPROPERTY(EditAnywhere, Category = "AI")
		float DespawnTimer = 3.f;
	UPROPERTY(EditAnywhere,Category = "AI")
		float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere, Category = "AI")
		float AIDamage = 30.f;
	UPROPERTY(EditAnywhere, Category = "AI")
		float PatrolSpeed = 150.f;
	UPROPERTY(EditAnywhere, Category = "AI")
		float ChaseSpeed = 400.f;
	UPROPERTY(EditAnywhere, Category = "AI")
		float AggroRange = 800.f;
	UPROPERTY(EditANywhere, Category = "AI")
		float AttackDelay = .7f;

	bool IsTakingDamage = false;
	//Check this to make AI friendly
	UPROPERTY(EditAnywhere)
		bool IsAIFriendly = false;
	float Health;

	//patrols between BotTargetPoints with the same index
	UPROPERTY(EditAnywhere, Category = "WaypointIndex")
		int32 WaypointIndex = 0;
	
	FTimerHandle TimerHandle;

	bool IsAlive = true;
	bool IsAggro = false;
	bool CanDoDamage = false;

	UPROPERTY(EditDefaultsOnly)
		USphereComponent* AttackRange = nullptr;
	UPROPERTY(EditAnywhere)
		USoundBase* HurtSound;

	AEnemyAIController* AIController = nullptr;
	AMainCharacter* Player = nullptr;

	void LineTraceToPlayer();
	FVector GetVectorTowardPlayer();
	void Despawn();

public:

	//Getters

	UFUNCTION(BlueprintCallable,Category = "EnemyAI")
		bool GetIsAlive() const { return IsAlive; }

	UFUNCTION(BlueprintCallable,Category = "EnemyAI")
		float GetHealthPercent() const { return Health / MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "EnemyAI")
		float GetHealth() const { return Health; }

	UFUNCTION()
		int32 GetWaypointIndex() const { return WaypointIndex; }

	UFUNCTION()
		float GetAIDamage() const { return AIDamage; }

	UFUNCTION(BlueprintCallable)
		bool GetIsAggro() const { return IsAggro; }

	UFUNCTION()
		bool GetCanDoDamage() const { return CanDoDamage; }

	UFUNCTION()
		float GetAttackDelay() const { return AttackDelay; }

	UFUNCTION(BlueprintCallable)
		bool GetIsTakingDamage() const { return IsTakingDamage; }

	//Setters

	UFUNCTION(BlueprintCallable, Category = "AI")
		void SetTakeDamage(float Damage);
		
};

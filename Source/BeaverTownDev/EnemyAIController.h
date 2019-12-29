// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
class UBehaviorTreeComponent;
class AEnemyAI;

UCLASS()
class BEAVERTOWNDEV_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
private:


	UBehaviorTreeComponent* BehaviorComp;
	UBlackboardComponent* BlackboardComp;
	
	//Blackboard Keys
	const FName BlackboardPlayerKey = FName("Player");
	const FName BlackboardIsAliveKey = FName("AIAlive?");
	const FName BlackboardIsAggroKey = FName("AIAggro?");
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName LocationToGoKey;
	

	AEnemyAI* EnemyAI = nullptr;
	TArray<AActor*> BotTargetPoints;
	FTimerHandle TimerHandle;
	
	bool AIAttackReset = true;
	bool IsAttacking = false;

	void AttackDelayEnd();
	virtual void OnPossess(APawn* Pawn) override;

public:

	AEnemyAIController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() const { return BotTargetPoints; }

	UFUNCTION()
		void Attack();

	UFUNCTION()
		void SetIsAliveBlackboardKey(bool IsAlive);

	UFUNCTION()
		void SetIsAggro(bool Aggro);

	UFUNCTION(BlueprintCallable)
		bool GetIsAttacking() const { return IsAttacking; }
	
};

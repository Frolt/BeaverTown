// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TargetPointSelectionTask.generated.h"

/**
 * Finds and sets patrolpoints for AI. AI will move to BotTargetPoints with matching indexes as EnemyAI
 * When AI reaches the Waypoint, random search for new point
 */
class ABotTargetPoint;
class AEnemyAI;

UCLASS()
class BEAVERTOWNDEV_API UTargetPointSelectionTask : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	ABotTargetPoint* BotWaypoint;
	AEnemyAI* EnemyWaypoint;	
};

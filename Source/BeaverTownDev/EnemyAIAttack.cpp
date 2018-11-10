// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIAttack.h"
#include "BeaverTownDev.h"
#include "EnemyAIController.h"
#include "EnemyAI.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UEnemyAIAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{	
		//A task run in Behavior Tree. When conditions inside behavior tree is met, run Attack function from AI Controller
		AIController->Attack();
		
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}



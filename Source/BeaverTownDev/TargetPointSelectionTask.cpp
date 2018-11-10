// Fill out your copyright notice in the Description page of Project Settings.

#include "TargetPointSelectionTask.h"
#include "BeaverTownDev.h"
#include "BotTargetPoint.h"
#include "EnemyAIController.h"
#include "EnemyAI.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UTargetPointSelectionTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	
	if (AIController)
	{
		//Matching waypoint index on EnemyAI and BotTargetPoints decides where the AI Will patrol.
		int32 EnemyWaypointIndex = Cast<AEnemyAI>(AIController->GetCharacter())->GetWaypointIndex();

		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComp();

		ABotTargetPoint* CurrentPoint = Cast<ABotTargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		//Finds all BotTargetPoints via EnemyAIController. Stored in an array to recieve random waypoint for the bot to use via Behavior tree.
		TArray<AActor*> AvailableTargetPoints = AIController->GetAvailableTargetPoints();

		int32 RandomIndex;

		//Stores the next possible waypoint for bots
		ABotTargetPoint* NextTargetPoint = nullptr;
		
			do {
				RandomIndex = FMath::RandRange(0, AvailableTargetPoints.Num() - 1);
				NextTargetPoint = Cast<ABotTargetPoint>(AvailableTargetPoints[RandomIndex]);

				if (NextTargetPoint->GetWaypointIndex() == EnemyWaypointIndex)
				{
					//Updates blackboard value with the next waypoint for AI.
					BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);
				}

		} while (CurrentPoint == NextTargetPoint);
	
			//return Successfull task
			return EBTNodeResult::Succeeded;
		
	}
	//Return failed task
	return EBTNodeResult::Failed;
}



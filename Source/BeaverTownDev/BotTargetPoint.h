// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "BotTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERTOWNDEV_API ABotTargetPoint : public ATargetPoint
{
	GENERATED_BODY()
	
	/*Class used to set specific waypoints for AI.*/
public:
	//Set index to match with AI's waypoint index. AI will only patrol between same index'ed waypoints
	UPROPERTY(EditAnywhere,Category = "WaypointIndex")
		int32 WaypointIndex = 0;
	
	UFUNCTION()
	 int32 GetWaypointIndex() const { return WaypointIndex; }
};

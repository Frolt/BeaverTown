// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TorchStatic.generated.h"

/*
Base for static torches
Most functionality is in blueprint
*/

UCLASS()
class BEAVERTOWNDEV_API ATorchStatic : public AActor
{
	GENERATED_BODY()
	
public:	
	ATorchStatic();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsLit;
};

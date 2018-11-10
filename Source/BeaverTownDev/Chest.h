// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact.h"
#include "Chest.generated.h"

/*
Chest that can be opened and closed by player.
Chest can also contain loot
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChestTriggerEvent);

UCLASS()
class BEAVERTOWNDEV_API AChest : public AInteract
{
	GENERATED_BODY()

public:
	AChest();
	// Overrides Open and Close functions from base class
	virtual void OpenEvent() override;
	virtual void CloseEvent() override;
	
	// Variables that broadcast to blueprint
	UPROPERTY(BlueprintAssignable)
		FChestTriggerEvent ChestOpen;
	UPROPERTY(BlueprintAssignable)
		FChestTriggerEvent ChestClose;

	// Chest options and loot text
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		FText LootTexts;
	UPROPERTY(BlueprintReadWrite)
		bool bLooted = false;
	UPROPERTY(EditAnywhere)
		bool bOpenOnce = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bHasLoot = false;
	FText GetLootText() const { return LootTexts; }

private:
	bool CanBeOpened = true;

	TArray<AActor*>ChestArray;
	void GetAllChestReferences();
};

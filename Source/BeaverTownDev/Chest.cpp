// Fill out your copyright notice in the Description page of Project Settings.

#include "Chest.h"
#include "BeaverTownDev.h"
#include "MainGameInstance.h"
#include "MainCharacter.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

AChest::AChest()
{
	// Sets variables declared in base class
	bOnlyInteractFromAngle = true;
	MinOpenAngle -= 45.f;
	MaxOpenAngle += 45.f;
}

// This function opens the chest and adds text according to settings.
void AChest::OpenEvent()
{
	if (bIsOpenEvent == false && CanBeOpened)
	{
		if (!bOpenOnce)
		{
			bIsOpenEvent = true;
		}
		// continues in blueprint
		ChestOpen.Broadcast();


		if (LootTexts.ToString() == TEXT("WoodKey"))
		{
			UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetWorld()->GetGameInstance());
			Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter())->SetOverheadText();
			GameInstance->SetWoodenKey(true);
			UE_LOG(LogTemp, Warning, TEXT("wOODKEY"))
		}
		if (bLooted == false)
		{
			if (LootTexts.ToString() == TEXT("WoodPart"))
			{
				UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetWorld()->GetGameInstance());
				Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter())->SetOverheadText();
				GameInstance->SetWoodParts();
				UE_LOG(LogTemp, Warning, TEXT("WoodParts::: %d"), GameInstance->GetWoodParts())
			}
		}
		CanBeOpened = false;
	}
}

// Close the chest
void AChest::CloseEvent()
{
	if (bIsOpenEvent == true)
	{
		bIsOpenEvent = false;
		// continues in blueprint
		ChestClose.Broadcast();
	}
}

void AChest::GetAllChestReferences()
{
	UGameplayStatics::GetAllActorsOfClass(this, AChest::StaticClass(), ChestArray);
}

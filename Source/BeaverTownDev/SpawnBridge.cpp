
#include "SpawnBridge.h"
#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "MainGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerVolume.h"


ASpawnBridge::ASpawnBridge()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnBridge::BeginPlay()
{
	Super::BeginPlay();
	
	BridgeMesh = FindComponentByClass<UStaticMeshComponent>();
	BridgeMesh->SetVisibility(false, true);
	this->SetActorEnableCollision(false);
}

void ASpawnBridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerCollectedWood = Cast<UMainGameInstance>(GetGameInstance())->GetWoodParts();
	if (PlayerCollectedWood >= BridgeIndex)
	{
		//Is ran for each WoodPart the player has collected, and builds the bridge piece by piece
		BuildBridge();
	}
}

void ASpawnBridge::BuildBridge()
{
	if (BridgeTrigger)
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

		if (BridgeTrigger->IsOverlappingActor(MainCharacter))
		{
			BridgeMesh->SetVisibility(true, true);
			this->SetActorEnableCollision(true);
		}
	}	
}
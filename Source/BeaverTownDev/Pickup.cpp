// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "MainGameInstance.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/Components/ShapeComponent.h"
#include "Engine/World.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sets up mesh, collision, root etc
	PickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot"));
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = PickupRoot;
	PickupMesh->SetupAttachment(RootComponent);
	PickupBox->SetupAttachment(RootComponent);
	PickupBox->SetGenerateOverlapEvents(true);
	PickupBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlap);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterPickup = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void APickup::OnOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (!CharacterPickup) { return; }

	// If PickupBox is overlapping with player, 
	// then destroy the box, play a sound, Spawn a particle, and heal the player
	if (PickupBox->IsOverlappingActor(CharacterPickup))
	{
		auto GameInstance = Cast<UMainGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			GameInstance->SetHealthIncrease(10);
			PlaySoundWhenPickup.Broadcast();
			if (HealthParticle)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HealthParticle, CharacterPickup->GetTransform(), true);
			}
			Destroy();
		}
	}
}



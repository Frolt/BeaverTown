// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageVolume.h"
#include "BeaverTownDev.h"
#include "MainGameInstance.h"
#include "MainCharacter.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ADamageVolume::ADamageVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootComponent = Root;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Box->SetupAttachment(RootComponent);
	Box->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void ADamageVolume::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UMainGameInstance>(GetWorld()->GetGameInstance());
	
}

// Called every frame
void ADamageVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Inflict damage to overlapping player if active
	if (Box->IsOverlappingActor(Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetCharacter())))
	{
			if (bPeriodicDamage && bActivate)
			{
				GameInstance->SetDamageTaken(DPS * DeltaTime);
			}
			else if(!bPeriodicDamage && bActivate)
			{
				GameInstance->SetDamageTaken(SingleDamage);
			}
	}
}

bool ADamageVolume::GetActivate()
{
	return bActivate;
}

void ADamageVolume::SetActivate(bool SetActivate)
{
	bActivate = SetActivate;
}

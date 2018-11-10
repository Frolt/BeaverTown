// Fill out your copyright notice in the Description page of Project Settings.

#include "RollingDoor.h"
#include "BeaverTownDev.h"
#include "BeaverTownDevGameModeBase.h"
#include "Engine/World.h"

// Sets default values
ARollingDoor::ARollingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARollingDoor::BeginPlay()
{
	Super::BeginPlay();

	auto GM = Cast<ABeaverTownDevGameModeBase>(GetWorld()->GetAuthGameMode());
	GM->SetDoor(this);
}

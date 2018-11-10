// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructibleRock.h"
#include "BeaverTownDev.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"


ADestructibleRock::ADestructibleRock()
{
	bCanBeDamaged = true;
}

void ADestructibleRock::OpenEvent()
{
	// Takes damage
	Health -= Damage;
	PlayRockHitSound();
	if (Health <= 0)
	{
		// continues in blueprint
		BreakRock();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetTransform(), true);
	}
}




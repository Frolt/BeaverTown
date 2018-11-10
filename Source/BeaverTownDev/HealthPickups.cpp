// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthPickups.h"
#include "BeaverTownDev.h"

AHealthPickups::AHealthPickups()
{

}

void AHealthPickups::BeginPlay()
{
	Super::BeginPlay();

}

float AHealthPickups::HealTarget()
{
	CanHeal = false;
	return HealingApplied;
}



// Fill out your copyright notice in the Description page of Project Settings.

#include "ThrowableItems.h"
#include "BeaverTownDev.h"
#include "MainCharacter.h"


AThrowableItems::AThrowableItems()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AThrowableItems::SetIsThrown(bool IsThrow)
{
	IsThrown = IsThrow;
}
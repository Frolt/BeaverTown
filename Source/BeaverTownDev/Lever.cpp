// Fill out your copyright notice in the Description page of Project Settings.

#include "Lever.h"
#include "BeaverTownDev.h"
#include "Pickup.h"
#include "Chest.h"

ALever::ALever()
{
	// Overrides settings from base class
	bOnlyInteractFromAngle = true;
	MinOpenAngle -= 20.f;
	MaxOpenAngle += 20.f;
}

void ALever::OpenEvent()
{
	if (bIsOpenEvent == false)
	{
		bIsOpenEvent = true;
		// Continues in blueprint
		LeverOpen.Broadcast();
	}
}

void ALever::CloseEvent()
{
	if (bIsOpenEvent == true)
	{
		bIsOpenEvent = false;
		// Continues in blueprint
		LeverClose.Broadcast();
	}
}




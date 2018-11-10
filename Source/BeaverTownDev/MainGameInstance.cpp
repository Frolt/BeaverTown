// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameInstance.h"
#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "Engine/World.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Public/TimerManager.h"

void UMainGameInstance::ResetStats()
{
	MaxHealth = 100.f;
	Health = MaxHealth;
	WoodenKey = false;
}

float UMainGameInstance::GetHealthPercent()
{
	return Health / MaxHealth;
}

//Inflict damage on player according to parameter value
void UMainGameInstance::SetDamageTaken(float Damage)
{
	AMainCharacter* PC = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	HurtSound = PC->GetHurtSound();
	Health -= Damage;
	IsTakingDamage = true;
	//Playe hurt sound only once when dead
	if (CanPlaySound &&  PlayHurtSoundOnceWhenDead)
	{
		CanPlaySound = false;
		
		UGameplayStatics::PlaySound2D(GetWorld(), HurtSound, 1.f, 1.f, 0.f);
		//Sets a timer before next hurt sound is played
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMainGameInstance::ResetCanPlaySound, SoundDelay, false);
		if (Health <= 0)
		{
			PlayHurtSoundOnceWhenDead = false;
		}
	}
	if (Health <= 0.f)
	{
		PC->SetIsPlayerAlive(false);
		LoadRestartGameUI();
	}
}

void UMainGameInstance::SetHealthIncrease(float inHealth)
{
	Health += inHealth;
	if (Health >= MaxHealth)
	{
		Health = MaxHealth;
	}
}

void UMainGameInstance::ResetHealth(float inHealth)
{
	Health = inHealth;
}

bool UMainGameInstance::GetWoodenKey()
{
	return WoodenKey;
}

void UMainGameInstance::SetWoodenKey(bool KeyStatus)
{
	WoodenKey = KeyStatus;
}

void UMainGameInstance::ResetCanPlaySound()
{
	CanPlaySound = true;
	IsTakingDamage = false;
}

void UMainGameInstance::SetWoodParts()
{
	if (WoodParts < 5)
	{
		WoodParts++;
	}
	
}
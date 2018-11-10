// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/EngineTypes.h"
#include "MainGameInstance.generated.h"

/*
Keeps track on players stats (items, health etc)
Also a has a lot of getters and setter to provide references to other classes.
*/

//Forward declaration
class AChest;

UCLASS()
class BEAVERTOWNDEV_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:

	//Player stats
	UPROPERTY(EditAnywhere, Category = "PlayerStats")
		float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere,Category = "PlayerStats")
		float Health = MaxHealth;
	UPROPERTY(EditAnywhere)
		USoundBase* HurtSound;

	bool WoodenKey = false;
	bool CanPlaySound = true;
	bool PlayHurtSoundOnceWhenDead = true;
	bool IsTakingDamage = false;
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere)
		float SoundDelay = 0.5f;
	UPROPERTY(EditAnywhere)
		USoundBase* Music;

	//Used for building a bridge in level2
	UPROPERTY(EditAnywhere)
		int32 WoodParts;

public:
	//Reset functions
	void ResetStats();
	void ResetCanPlaySound();
	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		void ResetHealth(float inHealth);
	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerStats")
		void LoadRestartGameUI();

	//Getter
	UFUNCTION(BlueprintCallable,Category = "PlayerStats")
		float GetHealthPercent();
	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		float GetMaxHealth() { return MaxHealth; }
	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		int32 GetWoodParts() { return WoodParts; }
	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		bool GetWoodenKey();
	UFUNCTION(BlueprintCallable)
		bool GetIsTakingDamage() const { return IsTakingDamage; }
	UFUNCTION(BlueprintCallable)
		float GetHealth() const { return Health; }

	//Setters
	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		void SetHealthIncrease(float inHealth);
	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		void SetDamageTaken(float Damage);
	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		void SetWoodParts();
	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		void SetWoodenKey(bool KeyStatus);

	//Save chest state
	UPROPERTY(BlueprintReadWrite)
		bool Chest1Looted = false;
	UPROPERTY(BlueprintReadWrite)
		bool Chest2Looted = false;
	UPROPERTY(BlueprintReadWrite)
		bool Chest3Looted = false;
	UPROPERTY(BlueprintReadWrite)
		bool Chest4Looted = false;
	UPROPERTY(BlueprintReadWrite)
		bool Chest5Looted = false;

};

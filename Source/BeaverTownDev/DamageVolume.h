// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageVolume.generated.h"

/*
Player take damage when overlapping with this actors collision
Can deal periodic or instant damage
*/

// Forward declarations
class UBoxComponent;
class UMainGameInstance;

UCLASS()
class BEAVERTOWNDEV_API ADamageVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
		bool GetActivate();
	UFUNCTION(BlueprintCallable, Category = "Damage")
		void SetActivate(bool SetActivate);

private:
	UPROPERTY(EditAnywhere, Category = "Damage")
		bool bPeriodicDamage = false;
	UPROPERTY(EditAnywhere, Category = "Damage")
		bool bActivate = true;
	UPROPERTY(EditAnywhere, Category = "Damage")
		float DPS = 10.f;
	UPROPERTY(EditAnywhere, Category = "Damage")
		float SingleDamage = 100.f;
	UPROPERTY(EditAnywhere, Category = "Damage")
		USceneComponent* Root = nullptr;
	UPROPERTY(EditAnywhere, Category = "Damage")
		UBoxComponent* Box = nullptr;

	UMainGameInstance* GameInstance = nullptr;
		
	
};


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

/*
The character controlled by the player
*/
class AChest;
class UCameraComponent;
class USpringArmComponent;
class UTextRenderComponent;

UCLASS()
class BEAVERTOWNDEV_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
		UCameraComponent* PlayerCamera = nullptr;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraBoom = nullptr;
	
	//Input Functions
	void MoveX(float value);
	void MoveY(float value);
	void Melee();
	void JumpPressed();
	void JumpReleased();
	void FallingDamage();
	void RotateToMousePosition(float DeltaTime);
	void Interact();
	void InteractReleased();
	void GetHitResultFromLineTrace(FHitResult &HitResult, float Reach);
	virtual void Landed(const FHitResult & Hit) override;
	void SetTextRotation(UTextRenderComponent* TextRenderComp);
	void SetVisibilityOverheadText();
	void TimerEnd();
	void MeleeDelayEnd();
	
	//Character Variables	
	UPROPERTY(EditAnywhere, Category = "CharacterStats")
		float InteractReach = 150.f;
	UPROPERTY(EditAnywhere, Category = "CharacterStats")
		float MeleeRange = 130.f;
	UPROPERTY(EditAnywhere, Category = "CharacterStats")
		float MeleeDamage = 30.f;
	UPROPERTY(EditAnywhere, Category = "CharacterStats")
		float OverheadTextDespawnTime = 2.f;
	UPROPERTY(EditAnywhere, Category = "CharacterStats")
		float AttackDelay = 0.3f;
	UPROPERTY(EditAnywhere, Category = "CharacterStats")
		float WalkSpeed = 400.f;
	UPROPERTY(EditAnywhere, Category = "CharacterStats")
		float WalkSpeedWhileAttacking = 300.f;
	UPROPERTY(EditAnywhere,Category = "CharacterStats")
		UParticleSystem* HealthParticle = nullptr;
	UPROPERTY(EditAnywhere, Category = "CharacterStats")
		UParticleSystem* MeleeParticle = nullptr;
	
	// Timer variables
	FTimerHandle TimerHandle;
	FTimerHandle MeleeTimerHandle;
	float StartJumpTime = 0;
	float EndJumpTime = 0;

	// Other variables
	bool bCanJump;	
	bool bIsInteractActive = false;
	bool IsPushingObject = false;
	bool bFalling = false;
	bool bCanTakeFallingDamage = false;
	bool IsTextVisible = false;
	bool CanMelee = true;
	bool IsPlayerAlive = true;
	bool IsThrowing = false;
	float TurnInterpolationSpeed = 1000.f;
	FText LootText;
	AChest* ChestRef = nullptr;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* HurtSound;
	UPROPERTY(EditAnywhere, Category = "TextRender")
		UTextRenderComponent* OverheadText;
public:
	//Character Getters	
	UFUNCTION(BlueprintCallable)
		bool GetIsInteractActive() const;
	UFUNCTION()
		float GetWalkSpeed() const { return WalkSpeed; }
	UFUNCTION(BlueprintCallable)
		bool GetCanMelee() const { return CanMelee; }
	UFUNCTION(BlueprintCallable)
		bool GetIsPlayerAlive() { return IsPlayerAlive; }
	UFUNCTION(BlueprintCallable)
		bool GetIsPushingObject() const { return IsPushingObject; }
	USoundBase* GetHurtSound();
	UFUNCTION(BlueprintCallable)
		bool GetIsThrowing() const { return IsThrowing; }

	//Setters
	void SetIsInteractActive(bool Status);	
	void SetIsPushingObject(bool IsPushing);
	void SetMaxWalkSpeed(float MovementSpeed);
	void SetOverheadText();
	UFUNCTION()
	void SetIsThrowing(bool Throwing) { IsThrowing = Throwing; }
	UFUNCTION(BlueprintCallable)
		void SetIsPlayerAlive(bool IsAlive) { IsPlayerAlive = IsAlive; }
	UFUNCTION(BlueprintCallable)
		void SetCanMelee(bool CanAttack) { CanMelee = CanAttack; }
	
};

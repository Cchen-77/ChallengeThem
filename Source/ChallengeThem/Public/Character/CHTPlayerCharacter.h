// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TopDownCharacter.h"
#include"Components/TimelineComponent.h"
#include"InputActionValue.h"
#include"GameBase/CHTResetInterface.h"
#include "CHTPlayerCharacter.generated.h"

/**
 * 
 */
class UPaperZDAnimationComponent;
class UPlayerHealthComponent;
class UBoxComponent;
class UInputMappingContext;
class UInputAction;
class UPlayerWeaponComponent;
class UPaperFlipbookComponent;
class UCurveFloat;
UCLASS()
class CHALLENGETHEM_API ACHTPlayerCharacter : public ATopDownCharacter, public ICHTResetInterface
{
	GENERATED_BODY()
public:
	ACHTPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void Reset() override;
	UFUNCTION(BlueprintCallable)
		void CheckWeaponCollision(int Mode);
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputMappingContext* IMC_PlayerDefault;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_MouseMove;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_Stab;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_Splash;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_Flash;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_Esc;
	UFUNCTION()
		virtual void OnMouseMove(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
		virtual void OnStab(const FInputActionValue& value);
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Actions)
	bool IsStabbing = false;
	UFUNCTION(BlueprintCallable)
		virtual void OnStabFinish();

	UFUNCTION(BlueprintCallable)
		virtual void OnSplash(const FInputActionValue& value);
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Actions)
	bool IsSplashing = false;
	UFUNCTION(BlueprintCallable)
		virtual void OnSplashFinish();

	UFUNCTION(BlueprintCallable)
		virtual void OnFlash(const FInputActionValue& value);
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Actions)
	bool IsFlashing = false;
	FTimeline InFlashingTimeline;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Flash)
		UCurveFloat* InFlashingCurve;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Flash)
		float FlashSpeed = 1000.0f;
	FVector FlashingDirection;
	UFUNCTION()
		virtual void InFlashing(float value);
	UFUNCTION(BlueprintCallable)
		virtual void OnFlashFinish();

	
	virtual void OnMove(const FInputActionValue& value) override;
	UFUNCTION(BlueprintCallable)
		virtual void OnHurt();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Actions)
	bool IsHurting = false;
	UFUNCTION(BlueprintCallable)
		virtual void OnHurtFinish();

	UFUNCTION(BlueprintCallable)
		virtual void OnDead();
	FTimerHandle OnDeadTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category = Actions)
	bool IsDead = false;

	UFUNCTION()
		void OnEsc();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UPlayerWeaponComponent* PlayerWeaponComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UBoxComponent* WeaponCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UPaperZDAnimationComponent* WeaponAnim;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UPaperFlipbookComponent* HandLayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UPlayerHealthComponent* PlayerHealthComponent;
	
	void SetWeaponTransform();
	void SetCursorPosition();
	void SetFaceDirection(bool FaceLeft);
	FVector2D Direction;

	UFUNCTION(BlueprintCallable)
	void Play2DMontage(int idx,FName MontageName);

	UFUNCTION(BlueprintCallable)
		void StartHitStop();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HitStop)
		float HitStopDuration = 0.1f;
	FTimerHandle HitStopTimer;
	UFUNCTION()
		void HitStopEnd();
};

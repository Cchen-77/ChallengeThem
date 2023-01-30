// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TopDownCharacter.h"
#include"InputActionValue.h"
#include"GameBase/CHTResetInterface.h"
#include "CHTPlayerCharacter.generated.h"

/**
 * 
 */
class UPlayerHealthComponent;
class UBoxComponent;
class UInputMappingContext;
class UInputAction;
class UPlayerWeaponComponent;
UCLASS()
class CHALLENGETHEM_API ACHTPlayerCharacter : public ATopDownCharacter, public ICHTResetInterface
{
	GENERATED_BODY()
public:
	ACHTPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void Reset() override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputMappingContext* IMC_PlayerDefault;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_MouseMove;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_Attack;
	UFUNCTION()
		virtual void OnMouseMove(const FInputActionValue& value);
	UFUNCTION()
		virtual void OnAttack(const FInputActionValue& value);
	virtual void OnMove(const FInputActionValue& value) override;
	UFUNCTION()
		virtual void OnDead();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UPlayerWeaponComponent* PlayerWeaponComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UBoxComponent* WeaponCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UPlayerHealthComponent* PlayerHealthComponent;
	void SetWeaponTransform();
	void SetCursorPosition();
};

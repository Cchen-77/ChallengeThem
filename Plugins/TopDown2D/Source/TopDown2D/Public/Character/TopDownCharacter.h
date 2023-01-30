// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include"InputActionValue.h"
#include "TopDownCharacter.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;
UCLASS()
class TOPDOWN2D_API ATopDownCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
public:
	ATopDownCharacter();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputMappingContext* IMC_Move;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputAction* IA_Move;
	UFUNCTION()
		virtual void OnMove(const FInputActionValue& value);

};

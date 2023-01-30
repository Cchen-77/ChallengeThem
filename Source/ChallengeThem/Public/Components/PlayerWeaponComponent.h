// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "PlayerWeaponComponent.generated.h"

/**
 * 
 */
class UBoxComponent;
UCLASS()
class CHALLENGETHEM_API UPlayerWeaponComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()
public:
	UPlayerWeaponComponent();
	void SetWeaponTransform(FVector2D Direction);
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		float HandDistance = 50.0f;
};

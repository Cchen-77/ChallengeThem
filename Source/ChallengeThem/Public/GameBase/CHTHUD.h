// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHTHUD.generated.h"

/**
 * 
 */
class UCursorLocatorWidget;
UCLASS()
class CHALLENGETHEM_API ACHTHUD : public AHUD
{
	GENERATED_BODY()
public:
	ACHTHUD();
	UFUNCTION()
		virtual void SetCursorPosition(float X, float Y);
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = Widgets)
		TSubclassOf<UCursorLocatorWidget> CursorLocatorWidgetClass;
	UPROPERTY()
		UCursorLocatorWidget* CursorLocatorWidget;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CursorLocatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGETHEM_API UCursorLocatorWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void SetCursorPosition(float X, float Y);
};

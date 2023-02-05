// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHTHUD.generated.h"

/**
 * 
 */
class UCursorLocatorWidget;
class UPlayerHealthWidget;
class UOpenMenuWidget;
class UEscMenuWidget;
class URestartWidget;
UCLASS()
class CHALLENGETHEM_API ACHTHUD : public AHUD
{
	GENERATED_BODY()
public:
	ACHTHUD();
	UFUNCTION()
		virtual void SetCursorPosition(float X, float Y);
	UFUNCTION(BlueprintCallable)
		void ShowCursorLocatorWidget();
	UFUNCTION(BlueprintCallable)
		void ShowPlayerHealthWidget();
	UFUNCTION(BlueprintCallable)
		void ShowOpenMenuWidget();
	UFUNCTION(BlueprintCallable)
		void ShowEscMenuWidget();
	UFUNCTION(BlueprintCallable)
		void ShowRestartWidget();
	UFUNCTION(BlueprintCallable)
		void RemoveEscMenuWidget();
	UFUNCTION(BlueprintCallable)
		void ShowCheckpointWidget();
	UFUNCTION(BlueprintCallable)
		void ShowFinishWidget();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = Widgets)
		TSubclassOf<UCursorLocatorWidget> CursorLocatorWidgetClass;
	UPROPERTY()
		UCursorLocatorWidget* CursorLocatorWidget;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
		TSubclassOf<UPlayerHealthWidget> PlayerHealthWidgetClass;
	UPROPERTY()
		UPlayerHealthWidget* PlayerHealthWidget;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
		TSubclassOf<UOpenMenuWidget> OpenMenuWidgetClass;
	UPROPERTY()
		UOpenMenuWidget* OpenMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
		TSubclassOf<UEscMenuWidget> EscMenuWidgetClass;
	UPROPERTY()
		UEscMenuWidget* EscMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
		TSubclassOf<URestartWidget> RestartWidgetClass;
	UPROPERTY()
		URestartWidget* RestartWidget;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
		TSubclassOf<UUserWidget> CheckpointWidgetClass;
	UPROPERTY()
		UUserWidget* CheckpointWidget;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
		TSubclassOf<UUserWidget> FinishWidgetClass;
	UPROPERTY()
		UUserWidget* FinishWidget;
};

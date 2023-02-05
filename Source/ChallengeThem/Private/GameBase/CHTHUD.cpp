// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBase/CHTHUD.h"
#include"Kismet/GameplayStatics.h"
#include"UI/CursorLocatorWidget.h"
#include"UI/PlayerHealthWidget.h"
#include"UI/OpenMenuWidget.h"
#include"UI/EscMenuWidget.h"
#include"UI/RestartWidget.h"
#include"UI/DialogueWidget.h"
#include"Blueprint/WidgetBlueprintLibrary.h"
ACHTHUD::ACHTHUD() {

}
void ACHTHUD::BeginPlay() {
	Super::BeginPlay();
}
void ACHTHUD::SetCursorPosition(float X,float Y) {
	CursorLocatorWidget->SetCursorPosition(X, Y);
}

void ACHTHUD::ShowCursorLocatorWidget() {
	if (!CursorLocatorWidget) {
		CursorLocatorWidget = CreateWidget<UCursorLocatorWidget>(GetOwningPlayerController(), CursorLocatorWidgetClass);
	}
	if (CursorLocatorWidget) {
		CursorLocatorWidget->AddToViewport();
	}
}

void ACHTHUD::ShowPlayerHealthWidget()
{
	if (!PlayerHealthWidget) {
		PlayerHealthWidget = CreateWidget<UPlayerHealthWidget>(GetOwningPlayerController(), PlayerHealthWidgetClass);
	}
	if (PlayerHealthWidget) {
		PlayerHealthWidget->AddToViewport();
	}
}

void ACHTHUD::ShowOpenMenuWidget()
{
	if (!OpenMenuWidget) {
		OpenMenuWidget = CreateWidget<UOpenMenuWidget>(GetOwningPlayerController(), OpenMenuWidgetClass);
	}
	if (OpenMenuWidget) {
		OpenMenuWidget->AddToViewport();
		GetOwningPlayerController()->SetInputMode(FInputModeUIOnly{});
		GetOwningPlayerController()->bShowMouseCursor = true;
		OpenMenuWidget->SetFocus();
	}
}

void ACHTHUD::ShowEscMenuWidget() 
{
	if (!EscMenuWidget) {
		EscMenuWidget = CreateWidget<UEscMenuWidget>(GetOwningPlayerController(), EscMenuWidgetClass);
	}
	if (EscMenuWidget) {
		EscMenuWidget->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		GetOwningPlayerController()->SetInputMode(FInputModeUIOnly{});
		GetOwningPlayerController()->bShowMouseCursor = true;
		EscMenuWidget->SetFocus();
		
		
	}
}
void ACHTHUD::RemoveEscMenuWidget() {
	if (EscMenuWidget) {
		EscMenuWidget->RemoveFromParent();
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		GetOwningPlayerController()->SetInputMode(FInputModeGameOnly{});
		GetOwningPlayerController()->bShowMouseCursor = false;
		UWidgetBlueprintLibrary::SetFocusToGameViewport();
	}
}
void ACHTHUD::ShowRestartWidget()
{
	if (!RestartWidget) {
		RestartWidget = CreateWidget<URestartWidget>(GetOwningPlayerController(), RestartWidgetClass);
	}
	if (RestartWidget) {
		RestartWidget->AddToViewport();
	}
}
void ACHTHUD::ShowCheckpointWidget() {
	if (!CheckpointWidget) {
		CheckpointWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), CheckpointWidgetClass);
	}
	if (CheckpointWidget) {
		CheckpointWidget->AddToViewport();
	}
}
void ACHTHUD::ShowFinishWidget() {
	if (!FinishWidget) {
		FinishWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), FinishWidgetClass);
	}
	if (FinishWidget) {
		FinishWidget->AddToViewport();
		GetOwningPlayerController()->SetInputMode(FInputModeUIOnly{});
		GetOwningPlayerController()->bShowMouseCursor = true;
		FinishWidget->SetFocus();
	}
}
void ACHTHUD::ShowDialogueWidget(const TArray<FString>& Texts) {
	if (!DialogueWidget) {
		DialogueWidget = CreateWidget<UDialogueWidget>(GetOwningPlayerController(), DialogueWidgetClass);
	}
	if (DialogueWidget) {
		DialogueWidget->InitTexts();
		DialogueWidget->SetTexts(Texts);
		DialogueWidget->AddToViewport();
		GetOwningPlayerController()->SetInputMode(FInputModeUIOnly{});
		DialogueWidget->SetFocus();

	}
}
void ACHTHUD::RemoveDialogueWidget() {
	if (DialogueWidget) {
		DialogueWidget->RemoveFromParent();
		GetOwningPlayerController()->SetInputMode(FInputModeGameOnly{});
		GetOwningPlayerController()->bShowMouseCursor = false;
		UWidgetBlueprintLibrary::SetFocusToGameViewport();
	}
}
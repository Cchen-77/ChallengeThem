// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBase/CHTHUD.h"
#include"UI/CursorLocatorWidget.h"
ACHTHUD::ACHTHUD() {

}
void ACHTHUD::BeginPlay() {
	Super::BeginPlay();
	CursorLocatorWidget = Cast<UCursorLocatorWidget>(CreateWidget<UUserWidget>(GetOwningPlayerController(),CursorLocatorWidgetClass));
	//check(CursorLocatorWidget);
	CursorLocatorWidget->AddToViewport();
}
void ACHTHUD::SetCursorPosition(float X,float Y) {
	CursorLocatorWidget->SetCursorPosition(X, Y);
}

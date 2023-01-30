// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CHTPlayerController.h"
#include"UI/CursorLocatorWidget.h"
#include"Blueprint/WidgetBlueprintLibrary.h"
#include"Camera/CameraActor.h"
#include"GameBase/CHTGameInstance.h"
#include"GameBase/CHTGameStateBase.h"
ACHTPlayerController::ACHTPlayerController() {

}
void ACHTPlayerController::BeginPlay() {
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
	UWidgetBlueprintLibrary::SetFocusToGameViewport();
}
void ACHTPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
void ACHTPlayerController::CameraFollow(float DeltaTime) {
	if (CameraForLevel) {
		if (auto TopDownCharacter = GetPawn()) {
			if (GetTopDownCamera()) {
				FVector Dest = TopDownCharacter->GetActorLocation();
				Dest.Z = CameraHeight;
				FVector From = TopDownCamera->GetActorLocation();
				if (Dest.X < From.X) return;
				Dest.Y = From.Y;
				FVector Res = FMath::VInterpTo(From, Dest, DeltaTime, CameraLagSpeed);
				if (IsCameraLag) {
					GetTopDownCamera()->SetActorLocation(Res);
				}
				else {
					GetTopDownCamera()->SetActorLocation(Dest);
				}
			}
		}
	}
	else {
		Super::CameraFollow(DeltaTime);
	}
}
void ACHTPlayerController::SetCameraToPawn() {
	FVector Dest = GetPawn()->GetActorLocation();
	Dest.Y = 0;
	Dest.Z = CameraHeight;
	GetTopDownCamera()->SetActorLocation(Dest);
}
void ACHTPlayerController::CHTRespawn()
{
	if (auto CHTGameInstance = Cast<UCHTGameInstance>(GetGameInstance())) {
		APawn* NewPawn = CHTGameInstance->ResetToCheckpoint();
		Possess(NewPawn);
		SetCameraToPawn();
	}
}

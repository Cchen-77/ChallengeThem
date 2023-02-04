// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CHTPlayerController.h"
#include"UI/CursorLocatorWidget.h"
#include"Blueprint/WidgetBlueprintLibrary.h"
#include"Camera/CameraActor.h"
#include"GameBase/CHTGameInstance.h"
#include"GameBase/CHTGameStateBase.h"
#include"GameBase/CHTHUD.h"
#include"Kismet/KismetSystemLibrary.h"
#include"GameBase/CHTAirWall.h"
ACHTPlayerController::ACHTPlayerController() {

}
void ACHTPlayerController::BeginPlay() {
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
	UWidgetBlueprintLibrary::SetFocusToGameViewport();
	InitCameraAndWall();
	if (auto CHTHUD = Cast<ACHTHUD>(GetHUD())) {
		CHTHUD->ShowCursorLocatorWidget();
		CHTHUD->ShowPlayerHealthWidget();
	}
}
void ACHTPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
void ACHTPlayerController::CameraFollow(float DeltaTime) {
	if (!CameraLocked) return;
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
	WallFollow();
}
void ACHTPlayerController::WallFollow() {
	auto CameraX = GetTopDownCamera()->GetActorLocation().X;
	if (WallLeft) {
		WallLeft->SetActorLocation(FVector(CameraX - WallHalfDistance, 0, 0));
	}
	if (WallRight) {
		WallRight->SetActorLocation(FVector(CameraX + WallHalfDistance, 0, 0));
	}
}
void ACHTPlayerController::InitCameraAndWall() {

	if (UKismetSystemLibrary::IsValid(WallLeft)) {
		WallLeft->Destroy();
	}
	if (UKismetSystemLibrary::IsValid(WallRight)) {
		WallRight->Destroy();
	}
	FVector Dest = GetPawn()->GetActorLocation();
	Dest.Y = 0;
	Dest.Z = CameraHeight;
	GetTopDownCamera()->SetActorLocation(Dest);
	auto CameraX = GetTopDownCamera()->GetActorLocation().X;
	FVector LLocation = FVector(CameraX - WallHalfDistance, 0, 0);
	FVector RLocation = FVector(CameraX + WallHalfDistance, 0, 0);
	FRotator Rotation;
	WallLeft = Cast<ACHTAirWall>(GetWorld()->SpawnActor(AirWallClass,&LLocation, &Rotation));
	WallRight = Cast<ACHTAirWall>(GetWorld()->SpawnActor(AirWallClass, &RLocation, &Rotation));
}
void ACHTPlayerController::CHTRespawn()
{
	if (auto CHTHUD = Cast<ACHTHUD>(GetHUD())) {
		CHTHUD->ShowRestartWidget();
	}
	GetWorld()->GetTimerManager().SetTimer(ResetTimer, this, &ACHTPlayerController::OnReset, 0.5);
}
void ACHTPlayerController::OnReset() {

	if (auto CHTGameInstance = Cast<UCHTGameInstance>(GetGameInstance())) {
		APawn* NewPawn = CHTGameInstance->ResetToCheckpoint();
		Possess(NewPawn);
		InitCameraAndWall();
		CameraLocked = true;
	}
}
void ACHTPlayerController::OnEsc() {
	if (auto CHTHUD = Cast<ACHTHUD>(GetHUD())) {
		CHTHUD->ShowEscMenuWidget();
	}
}
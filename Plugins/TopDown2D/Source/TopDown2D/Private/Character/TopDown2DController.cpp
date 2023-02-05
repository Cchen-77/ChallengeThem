// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TopDown2DController.h"
#include"Camera/CameraActor.h"
#include"Camera/CameraComponent.h"
ATopDown2DController::ATopDown2DController() {
	bAutoManageActiveCameraTarget = false;
}
void ATopDown2DController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CameraFollow(DeltaTime);
}
void ATopDown2DController::BeginPlay()
{
	Super::BeginPlay();
	TopDownCamera = GetWorld()->SpawnActor<ACameraActor>();
	TopDownCamera->SetOwner(this);
	TopDownCamera->SetActorLocation(FVector(0, 0, CameraHeight));
	TopDownCamera->SetActorRotation(FRotator(-90, -90, 0));
	if (IsCameraPerspective) {
		TopDownCamera->GetCameraComponent()->SetProjectionMode(ECameraProjectionMode::Perspective);
	}
	else {
		TopDownCamera->GetCameraComponent()->SetProjectionMode(ECameraProjectionMode::Orthographic);
		TopDownCamera->GetCameraComponent()->SetOrthoWidth(CameraOrthoWidth);
	}
	TopDownCamera->GetCameraComponent()->bConstrainAspectRatio = false;
	SetViewTarget(TopDownCamera);
}

void ATopDown2DController::CameraFollow(float DeltaTime)
{
	if (!CameraLocked) return;
	if (auto TopDownCharacter = GetPawn()) {
		if (TopDownCamera) {
			FVector Dest = TopDownCharacter->GetActorLocation();
			Dest.Z = CameraHeight;
			FVector From = TopDownCamera->GetActorLocation();
			FVector Res = FMath::VInterpTo(From, Dest, DeltaTime, CameraLagSpeed);
			if (IsCameraLag) {
				TopDownCamera->SetActorLocation(Res);
			}
			else {
				TopDownCamera->SetActorLocation(Dest);
			}
		}
	}
}
ACameraActor* ATopDown2DController::GetTopDownCamera() const {
	return TopDownCamera;
}
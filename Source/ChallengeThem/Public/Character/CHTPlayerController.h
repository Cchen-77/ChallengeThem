// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TopDown2DController.h"
#include "CHTPlayerController.generated.h"

/**
 * 
 */
class ACHTAirWall;
class UCursorLocatorWidget;
UCLASS()
class CHALLENGETHEM_API ACHTPlayerController : public ATopDown2DController
{
	GENERATED_BODY()
public:
	ACHTPlayerController();
	virtual void Tick(float DeltaTime) override;	
	UFUNCTION(BlueprintCallable)
		void InitCameraAndWall();
	UFUNCTION(BlueprintCallable)
	void CHTRespawn();
	UFUNCTION()
		void OnEsc();
	void StartHitShake();
	void SetCameramaxx(float x);
	void FinishGame();
protected:
	virtual void BeginPlay() override;
	virtual void CameraFollow(float DeltaTime) override;
	UPROPERTY(EditDefaultsOnly, Category = AirWall)
		TSubclassOf<ACHTAirWall> AirWallClass;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		float Cameramaxx = 0;
	virtual void WallFollow();
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		bool CameraForLevel = true;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		TSubclassOf<UCameraShakeBase> HitShakeClass;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		float WallHalfDistance = 100.0f;
	UPROPERTY()
		ACHTAirWall* WallLeft;
	UPROPERTY()
		ACHTAirWall* WallRight;
	UFUNCTION()
		void OnReset();
	FTimerHandle ResetTimer;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TopDown2DController.h"
#include "CHTPlayerController.generated.h"

/**
 * 
 */
class UCursorLocatorWidget;
UCLASS()
class CHALLENGETHEM_API ACHTPlayerController : public ATopDown2DController
{
	GENERATED_BODY()
public:
	ACHTPlayerController();
	virtual void Tick(float DeltaTime) override;	
	UFUNCTION(BlueprintCallable)
		void SetCameraToPawn();
protected:
	virtual void BeginPlay() override;
	virtual void CameraFollow(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		bool CameraForLevel = true;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		float MAXLeftMoveDistance = 100.0f;
	UFUNCTION(BlueprintCallable)
	void CHTRespawn();
};

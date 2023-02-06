// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CHTBaseEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGETHEM_API ACHTBaseEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	ACHTBaseEnemyController();
	UFUNCTION()
		void OnEnemyDead();
	UFUNCTION()
		void Wakeup();
protected:
	virtual void OnPossess(APawn* InPawn) override;
};

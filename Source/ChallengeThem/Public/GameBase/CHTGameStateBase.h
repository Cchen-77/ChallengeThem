// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CHTGameStateBase.generated.h"

/**
 * 
 */
class ACHTCheckpoint;
UCLASS()
class CHALLENGETHEM_API ACHTGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	void SetCheckpoint(ACHTCheckpoint* CHTCheckpoint);
	ACHTCheckpoint* GetCheckpoint() const;
protected:
	ACHTCheckpoint* Checkpoint = nullptr;
};

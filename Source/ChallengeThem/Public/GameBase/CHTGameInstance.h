// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include"GameBase/TopDownCharacterManager.h"
#include "CHTGameInstance.generated.h"

/**
 * 
 */
class ATopDownCharacter;
UCLASS()
class CHALLENGETHEM_API UCHTGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	TopDownCharacterManager CHTCharacterManager;
	void RegisterToCharacterManager(ATopDownCharacter* CHTCharacter);
	APawn* ResetToCheckpoint();
};

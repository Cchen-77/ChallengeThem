// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ATopDownCharacter;
class CHALLENGETHEM_API TopDownCharacterManager
{
public:
	TopDownCharacterManager();
	void Register(ATopDownCharacter* Character);
	void DestroyAll();
protected:
	TArray<ATopDownCharacter*> TopDownCharacters;
};

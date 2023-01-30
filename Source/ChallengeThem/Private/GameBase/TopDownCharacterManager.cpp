// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBase/TopDownCharacterManager.h"
#include"Character/TopDownCharacter.h"
#include"Kismet/KismetSystemLibrary.h"
TopDownCharacterManager::TopDownCharacterManager()
{
	TopDownCharacters.Empty();
}
void TopDownCharacterManager::Register(ATopDownCharacter * Character)
{
	TopDownCharacters.Add(Character);
}
void TopDownCharacterManager::DestroyAll()
{
	for (auto Character : TopDownCharacters) {
		if (Character&&UKismetSystemLibrary::IsValid(Character)) {
			Character->Destroy();
		}
	}
	TopDownCharacters.Empty();
}


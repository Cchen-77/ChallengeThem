// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHealthWidget.h"
#include"Character/CHTPlayerCharacter.h"
#include"Components/PlayerHealthComponent.h"
float UPlayerHealthWidget::GetPlayerHealth() {
	if (auto Player = GetOwningPlayerPawn()) {
		if (auto HealthComponent = Cast<UPlayerHealthComponent>(Player->GetComponentByClass(UPlayerHealthComponent::StaticClass()))) {
			return HealthComponent->GetHealth();
		}
	}
	return 0;
}
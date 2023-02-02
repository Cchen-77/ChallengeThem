// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerWeaponComponent.h"
#include"Components/BoxComponent.h"
UPlayerWeaponComponent::UPlayerWeaponComponent() {

}
void UPlayerWeaponComponent::BeginPlay() {
	Super::BeginPlay();
	SetWeaponTransform(FVector2D(1, 0));
}
void UPlayerWeaponComponent::SetWeaponTransform(FVector2D Direction) {
	

	float Up = -1;
	float Radians = FMath::Acos(Direction.X);	
	if (Direction.Y > 0) {
		Radians = 2 * FMath::Acos(-1) - Radians;
		Up = 1;
	}
	float Degree = FMath::RadiansToDegrees(Radians);	
	SetRelativeLocation(FVector(Direction.X * HandDistance, Up, -Direction.Y * HandDistance));
	SetRelativeRotation(FRotator(Degree, 0, 0));

}
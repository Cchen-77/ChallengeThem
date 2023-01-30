// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TopDownCharacter.h"
#include"Kismet/GameplayStatics.h"
#include"EnhancedInputSubsystems.h"
#include"EnhancedInputComponent.h"
#include"Character/TopDown2DController.h"
ATopDownCharacter::ATopDownCharacter() {

}
void ATopDownCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ATopDownCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (auto PlayerController = Cast<APlayerController>(GetController())) {
		if (auto Subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			if(IMC_Move)
				Subsys->AddMappingContext(IMC_Move,0);
		}
	}
}
void ATopDownCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		if(IA_Move)
			EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ATopDownCharacter::OnMove);
	}
}
void ATopDownCharacter::OnMove(const FInputActionValue& value) {
	FVector2D Direction = value.Get<FVector2D>();
	AddMovementInput(FVector(Direction.X, -Direction.Y, 0));
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CHTPlayerCharacter.h"
#include"Character/CHTPlayerController.h"
#include"GameBase/CHTHUD.h"
#include"EnhancedInputSubsystems.h"
#include"EnhancedInputComponent.h"
#include"PaperFlipbookComponent.h"
#include"Kismet/GameplayStatics.h"
#include"Blueprint/WidgetLayoutLibrary.h"
#include"Components/PlayerWeaponComponent.h"
#include"Character/CHTWeaponCollision.h"
#include"Components/PlayerHealthComponent.h"
#include"Enemy/CHTWeakpointCollision.h"
#include"GameBase/CHTGameInstance.h"
ACHTPlayerCharacter::ACHTPlayerCharacter() {
	PlayerWeaponComponent = CreateDefaultSubobject<UPlayerWeaponComponent>("PlayerWeaponComponent");
	PlayerWeaponComponent->SetupAttachment(GetSprite());
	WeaponCollision = CreateDefaultSubobject<UCHTWeaponCollision>("WeaponCollision");
	WeaponCollision->SetupAttachment(PlayerWeaponComponent);
	PlayerHealthComponent = CreateDefaultSubobject<UPlayerHealthComponent>("PlayerHealthComponent");
}
void ACHTPlayerCharacter::BeginPlay() {
	Super::BeginPlay();
	check(PlayerWeaponComponent);
	check(WeaponCollision);
	check(PlayerHealthComponent);
	//ADD IMC
	if (auto PC = Cast<APlayerController>(GetController())) {
		if (auto Subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) {
			if(IMC_PlayerDefault)
				Subsys->AddMappingContext(IMC_PlayerDefault,1);
		}
	}
	
	OnTakeAnyDamage.AddDynamic(PlayerHealthComponent, &UPlayerHealthComponent::TakeDamage);
	PlayerHealthComponent->OnPlayerDead.AddDynamic(this, &ACHTPlayerCharacter::OnDead);

	if (auto CHTGameInstance = Cast<UCHTGameInstance>(GetGameInstance())) {
		CHTGameInstance->RegisterToCharacterManager(this);
	}
}
void ACHTPlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
void ACHTPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (auto EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		if(IA_MouseMove)
			EnhancedInput->BindAction(IA_MouseMove, ETriggerEvent::Triggered, this, &ACHTPlayerCharacter::OnMouseMove);
		if(IA_Attack)
			EnhancedInput->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &ACHTPlayerCharacter::OnAttack);
	}
}
void ACHTPlayerCharacter::OnMouseMove(const FInputActionValue& value) {
	SetWeaponTransform();
	SetCursorPosition();
}

void ACHTPlayerCharacter::OnMove(const FInputActionValue& value)
{
	if (auto PC = Cast<ACHTPlayerController>(GetController())) {
		if (value.Get<FVector2D>().X != -1||PC->CanMoveLeft()) {
			Super::OnMove(value);
			SetWeaponTransform();
		}
	}
}
void ACHTPlayerCharacter::OnAttack(const FInputActionValue& value) {
	//UE_LOG(LogTemp, Display, TEXT("ATTACK!"));
	TArray<UPrimitiveComponent*> OverlappingComponents;
	WeaponCollision->GetOverlappingComponents(OverlappingComponents);
	for (auto TheComponent : OverlappingComponents) {
		if (TheComponent->IsA(UCHTWeakpointCollision::StaticClass())) {
			auto WeakpointCollision = Cast<UCHTWeakpointCollision>(TheComponent);
			WeakpointCollision->BeHit();
		}
	}
}
void ACHTPlayerCharacter::OnDead() {

}
void ACHTPlayerCharacter::SetWeaponTransform()
{
	if (auto PC = Cast<APlayerController>(GetController())) {
		FVector MouseLocation;
		FVector MouseDirection;
		PC->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
		FHitResult MouseHitResult;
		GetWorld()->LineTraceSingleByChannel(MouseHitResult, MouseLocation, MouseLocation + MouseDirection * 10000, ECollisionChannel::ECC_WorldStatic);
		MouseLocation = MouseHitResult.Location;
		FVector ActorCenter = GetSprite()->GetComponentLocation();
		FVector2D Direction = FVector2D(MouseLocation.X - ActorCenter.X, MouseLocation.Y - ActorCenter.Y);
		Direction.Normalize();
		PlayerWeaponComponent->SetWeaponTransform(Direction);
	}
}

void ACHTPlayerCharacter::SetCursorPosition()
{
	if (auto PC = Cast<APlayerController>(GetController())) {
		FVector2D MousePostionInVieport = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		if (auto CHTHUD = Cast<ACHTHUD>(PC->GetHUD())) {
			CHTHUD->SetCursorPosition(MousePostionInVieport.X, MousePostionInVieport.Y);
		}
	}
}

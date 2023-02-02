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
#include"GameFramework/CharacterMovementComponent.h"
#include"PaperFlipbookComponent.h"
#include"PaperZDAnimationComponent.h"
#include"PaperZDAnimInstance.h"

ACHTPlayerCharacter::ACHTPlayerCharacter() {
	HandLayer = CreateDefaultSubobject<UPaperFlipbookComponent>("HandLayer");
	HandLayer->SetupAttachment(GetRootComponent());
	PlayerWeaponComponent = CreateDefaultSubobject<UPlayerWeaponComponent>("PlayerWeaponComponent");
	PlayerWeaponComponent->SetupAttachment(HandLayer);
	WeaponCollision = CreateDefaultSubobject<UCHTWeaponCollision>("WeaponCollision");
	WeaponCollision->SetupAttachment(PlayerWeaponComponent);
	PlayerHealthComponent = CreateDefaultSubobject<UPlayerHealthComponent>("PlayerHealthComponent");
	WeaponAnim = CreateDefaultSubobject<UPaperZDAnimationComponent>("WeaponAnim");
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
	PlayerHealthComponent->OnPlayerHurt.AddDynamic(this, &ACHTPlayerCharacter::OnHurt);

	FOnTimelineFloat InFlashingEvent;
	InFlashingEvent.BindUFunction(this, "InFlashing");
	InFlashingTimeline.AddInterpFloat(InFlashingCurve,InFlashingEvent);
}
void ACHTPlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	InFlashingTimeline.TickTimeline(DeltaTime);
}
void ACHTPlayerCharacter::Reset() {
	Destroy();
}
void ACHTPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (auto EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		if(IA_MouseMove)
			EnhancedInput->BindAction(IA_MouseMove, ETriggerEvent::Triggered, this, &ACHTPlayerCharacter::OnMouseMove);
		if(IA_Stab)
			EnhancedInput->BindAction(IA_Stab, ETriggerEvent::Triggered, this, &ACHTPlayerCharacter::OnStab);
		if(IA_Splash)
			EnhancedInput->BindAction(IA_Splash, ETriggerEvent::Triggered, this, &ACHTPlayerCharacter::OnSplash);
		if (IA_Flash)
			EnhancedInput->BindAction(IA_Flash, ETriggerEvent::Triggered, this, &ACHTPlayerCharacter::OnFlash);

	}
}
void ACHTPlayerCharacter::OnMouseMove(const FInputActionValue& value) {
	SetWeaponTransform();
	SetCursorPosition();
}

void ACHTPlayerCharacter::OnMove(const FInputActionValue& value)
{
	Super::OnMove(value);
	SetWeaponTransform();
}

void ACHTPlayerCharacter::OnStab(const FInputActionValue& value) {
	
}
void ACHTPlayerCharacter::OnStabFinish() {

}

void ACHTPlayerCharacter::OnSplash(const FInputActionValue& value) {

}
void ACHTPlayerCharacter::OnSplashFinish() {

}
void ACHTPlayerCharacter::OnFlash(const FInputActionValue& value) {
	if (IsFlashing) return;
	IsFlashing = true;
	Play2DMontage("JumpToFlash");
	FlashingDirection = FVector(Direction.X, Direction.Y, 0);
	InFlashingTimeline.PlayFromStart();
}
void ACHTPlayerCharacter::InFlashing(float value){
	GetCharacterMovement()->Velocity = FlashingDirection * FlashSpeed*value;
}
void ACHTPlayerCharacter::OnFlashFinish() {
	IsFlashing = false;
}

void ACHTPlayerCharacter::OnHurt() {

}
void ACHTPlayerCharacter::OnHurtFinish() {

}

void ACHTPlayerCharacter::OnDead() {

}
void ACHTPlayerCharacter::CheckWeaponCollsion() {
	TArray<UPrimitiveComponent*> OverlappingComponents;
	WeaponCollision->GetOverlappingComponents(OverlappingComponents);
	for (auto TheComponent : OverlappingComponents) {
		if (TheComponent->IsA(UCHTWeakpointCollision::StaticClass())) {
			auto WeakpointCollision = Cast<UCHTWeakpointCollision>(TheComponent);
			WeakpointCollision->BeHit();
		}
	}
}
void ACHTPlayerCharacter::SetFaceDirection(bool FaceLeft) {

	if (!FaceLeft) {
		GetSprite()->SetWorldScale3D(FVector(-1, 1, 1));
		PlayerWeaponComponent->SetWorldScale3D(FVector(1, 1, -1));
	}
	else {
		GetSprite()->SetWorldScale3D(FVector(1, 1, 1));
		PlayerWeaponComponent->SetWorldScale3D(FVector(1, 1, 1));
	}
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
		Direction = FVector2D(MouseLocation.X - ActorCenter.X, MouseLocation.Y - ActorCenter.Y);
		Direction.Normalize();
		SetFaceDirection(Direction.X >= 0);
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

void ACHTPlayerCharacter::Play2DMontage(FName MontageName)
{
	if (auto CHTAnimInstance = GetAnimationComponent()->GetAnimInstance()) {
		CHTAnimInstance->JumpToNode(MontageName, "Montage");
	}
}
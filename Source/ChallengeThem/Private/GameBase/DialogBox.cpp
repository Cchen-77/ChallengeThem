// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBase/DialogBox.h"
#include"Components/BoxComponent.h"
#include"Kismet/GameplayStatics.h"
#include"Character/CHTPlayerController.h"
#include"GameBase/CHTHUD.h"
// Sets default values
ADialogBox::ADialogBox()
{
	PrimaryActorTick.bCanEverTick = false;
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	SetRootComponent(Collision);
	Texts.Empty();
}

void ADialogBox::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADialogBox::BeTouched);
}
void ADialogBox::BeTouched(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if (Touched) return;
	Touched = true;
	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) {
		if (auto PC = Cast<ACHTPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) {
			if (auto CHTHUD = Cast<ACHTHUD>(PC->GetHUD())) {
				CHTHUD->ShowDialogueWidget(Texts);
			}
		}
	}
}
void ADialogBox::Reset() {
	Touched = false;
}


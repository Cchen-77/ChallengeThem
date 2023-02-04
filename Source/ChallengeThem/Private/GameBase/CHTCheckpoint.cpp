// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBase/CHTCheckpoint.h"
#include"Components/BoxComponent.h"
#include"Character/CHTPlayerCharacter.h"
#include"Kismet/GameplayStatics.h"
#include"GameBase/CHTGameStateBase.h"
#include"GameBase/CHTHUD.h"
ACHTCheckpoint::ACHTCheckpoint()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	CheckpointCollision = CreateDefaultSubobject<UBoxComponent>("CheckpointCollision");
	SetRootComponent(CheckpointCollision);

}
void ACHTCheckpoint::BeginPlay()
{
	Super::BeginPlay();
	CheckpointCollision->OnComponentBeginOverlap.AddDynamic(this, &ACHTCheckpoint::ActorOverlapCheckpoint);
}
void ACHTCheckpoint::ActorOverlapCheckpoint(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA<ACHTPlayerCharacter>()&&!Checked) {
		Checked = true;
		if (auto CHTGameState = Cast<ACHTGameStateBase>(GetWorld()->GetGameState())) {
			CHTGameState->SetCheckpoint(this);
		}
		if (auto PC = UGameplayStatics::GetPlayerController(GetWorld(),0)) {
			if (auto CHTHUD = Cast<ACHTHUD>(PC->GetHUD())) {
				CHTHUD->ShowCheckpointWidget();
			}
		}
	}
}
void ACHTCheckpoint::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}




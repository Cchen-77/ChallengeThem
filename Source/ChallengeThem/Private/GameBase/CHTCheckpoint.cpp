// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBase/CHTCheckpoint.h"
#include"Components/BoxComponent.h"
#include"Character/CHTPlayerCharacter.h"
#include"GameBase/CHTGameStateBase.h"
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
			//test
			UE_LOG(LogTemp, Display, TEXT("Checkpoint!"));
		}
	}
}
void ACHTCheckpoint::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}




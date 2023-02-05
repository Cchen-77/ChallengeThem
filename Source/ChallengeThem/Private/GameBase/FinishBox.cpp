#include "GameBase/FinishBox.h"
#include"Components/BoxComponent.h"
#include"Kismet/GameplayStatics.h"
#include"Character/CHTPlayerController.h"
AFinishBox::AFinishBox()
{
	PrimaryActorTick.bCanEverTick = false;
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	SetRootComponent(Collision);
}

void AFinishBox::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AFinishBox::BeTouched);
}
void AFinishBox::BeTouched(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) {
		if (auto PC = Cast<ACHTPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) {
			PC->FinishGame();

		}
	}
}


#include "GameBase/CHTAirWall.h"
#include"Components/BoxComponent.h"
ACHTAirWall::ACHTAirWall()
{
	PrimaryActorTick.bCanEverTick = true;
	WallCollision = CreateDefaultSubobject<UBoxComponent>("WallCollison");
	WallCollision->SetBoxExtent(FVector(10, 5000, 5000));
	SetRootComponent(WallCollision);
}

void ACHTAirWall::BeginPlay()
{
	Super::BeginPlay();
}
void ACHTAirWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


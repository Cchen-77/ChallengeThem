#include "Enemy/CHTBaseEnemySpawner.h"
#include"Character/CHTPlayerCharacter.h"
#include"Components/BoxComponent.h"
#include"Enemy/CHTBaseEnemy.h"
ACHTBaseEnemySpawner::ACHTBaseEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnerCollision = CreateDefaultSubobject<UBoxComponent>("SpawnerCollsion");
	SetRootComponent(SpawnerCollision);
}
void ACHTBaseEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnerCollision->OnComponentBeginOverlap.AddDynamic(this, &ACHTBaseEnemySpawner::BeTouched);
}
void ACHTBaseEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ACHTBaseEnemySpawner::Reset() {
	Touched = false;
}
void ACHTBaseEnemySpawner::BeTouched(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if (OtherActor->IsA<ACHTPlayerCharacter>()) {
		if (!Touched) {
			Touched = true;
			StartSpawn();
		}
	}
}
void ACHTBaseEnemySpawner::StartSpawn() {
	for (auto EnemyInfo : EnemyInfos) {
		auto Rotator = FRotator();
		auto EnemyLocation = EnemyInfo.EnemyLocation;
		GetWorld()->SpawnActor(EnemyInfo.EnemyClass, &EnemyLocation, &Rotator);
	}
}

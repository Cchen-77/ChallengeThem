#include "Enemy/CHTBaseEnemySpawner.h"
#include"Character/CHTPlayerCharacter.h"
#include"Components/BoxComponent.h"
#include"Kismet/GameplayStatics.h"
#include"Character/CHTPlayerController.h"
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
	EnemyCounter = 0;
}
void ACHTBaseEnemySpawner::BeTouched(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if (OtherActor->IsA<ACHTPlayerCharacter>()) {
		if (!Touched) {
			Touched = true;
			StartSpawn();
			if (auto PC = Cast<ACHTPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) {
				PC->SetCameramaxx(GetActorLocation().X);
				PC->CameraLocked = false;
			}
		}
	}

}
void ACHTBaseEnemySpawner::StartSpawn() {
	for (auto EnemyInfo : EnemyInfos) {
		auto Rotator = FRotator();
		auto EnemyLocation = EnemyInfo.EnemyLocation;
		auto Enemy = Cast<ACHTBaseEnemy>(GetWorld()->SpawnActor(EnemyInfo.EnemyClass, &EnemyLocation, &Rotator));
		if (Enemy) {
			Enemy->OnEnemyDead.AddUObject(this, &ACHTBaseEnemySpawner::OnEnemyDead);
			++EnemyCounter;
		}
	}
}
void ACHTBaseEnemySpawner::OnEnemyDead() {
	--EnemyCounter;
	if (EnemyCounter == 0) {
		OnAllEnemyDead();
	}
}
void ACHTBaseEnemySpawner::OnAllEnemyDead() {
	if (auto PC = Cast<ACHTPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) {
		PC->CameraLocked = true;
	}
}

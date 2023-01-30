// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/CHTBaseEnemy.h"
#include"Enemy/CHTBaseEnemyController.h"
#include"Enemy/CHTBaseEnemyWeakpoint.h"
#include"Kismet/GameplayStatics.h"
#include"PaperFlipbookComponent.h"
#include"GameBase/CHTGameInstance.h"
#include"Kismet/KismetSystemLibrary.h"
ACHTBaseEnemy::ACHTBaseEnemy() {
	AIControllerClass = ACHTBaseEnemyController::StaticClass();
	WeakpointLayer = CreateDefaultSubobject<UPaperFlipbookComponent>("WeakpointLayer");
	WeakpointLayer->SetupAttachment(GetSprite());
}
void ACHTBaseEnemy::BeginPlay() {
	Super::BeginPlay();
	SpawnWeakpoints();
	if (auto CHTGameInstance = Cast<UCHTGameInstance>(GetGameInstance())) {
		CHTGameInstance->RegisterToCharacterManager(this);
	}
}
void ACHTBaseEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
void ACHTBaseEnemy::SpawnWeakpoints() {
	Weakpoint_1 = SpawnWeakpoint(1, HavWeakpoint_1);
	Weakpoint_2 = SpawnWeakpoint(2, HavWeakpoint_2);
	Weakpoint_3 = SpawnWeakpoint(3, HavWeakpoint_3);
	Weakpoint_4 = SpawnWeakpoint(4, HavWeakpoint_4);
}
ACHTBaseEnemyWeakpoint* ACHTBaseEnemy::SpawnWeakpoint(int WeakpointIndex,bool HavWeakpoint){
	if (!HavWeakpoint) return nullptr;
	++WeakpointCount;
	FName WeakpointSocket;
	switch (WeakpointIndex) {
		case 1:
			WeakpointSocket = "Weakpoint_1";
			break;
		case 2:
			WeakpointSocket = "Weakpoint_2";
			break;
		case 3:
			WeakpointSocket = "Weakpoint_3";
			break;
		case 4:
			WeakpointSocket = "Weakpoint_4";
			break;
	}
	FTransform TempTransform = FTransform();
	auto Weakpoint = Cast<ACHTBaseEnemyWeakpoint>(GetWorld()->SpawnActorDeferred<AActor>(WeakpointClass, TempTransform,this));
	check(Weakpoint);
	Weakpoint->SetOwningEnemy(this);
	Weakpoint->SetWeakpointIndex(WeakpointIndex);
	Weakpoint->SetRemainingHitTimes(MAXWeakpointHitTimes);
	UGameplayStatics::FinishSpawningActor(Weakpoint, TempTransform);
	Weakpoint->AttachToComponent(WeakpointLayer, FAttachmentTransformRules::SnapToTargetIncludingScale, WeakpointSocket);
	return Weakpoint;
}
void ACHTBaseEnemy::OnWeakpointBreak(int WeakpointIndex) {
	switch (WeakpointIndex) {
		case 1:
			HavWeakpoint_1 = false;
			break;
		case 2:
			HavWeakpoint_2 = false;
			break;
		case 3:
			HavWeakpoint_3 = false;
			break;
		case 4:
			HavWeakpoint_4 = false;
			break;
	}
	--WeakpointCount;
	//For test
	if (WeakpointCount == 0)
	{
		Destroy();
		if (auto EnemyController = Cast<ACHTBaseEnemyController>(GetController())) {
			EnemyController->OnEnemyDead();
		}
	}
}
void ACHTBaseEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason){
	
	if (UKismetSystemLibrary::IsValid(Weakpoint_1)) {
		Weakpoint_1->Destroy();
	}
	if (UKismetSystemLibrary::IsValid(Weakpoint_2)) {
		Weakpoint_2->Destroy();
	}
	if (UKismetSystemLibrary::IsValid(Weakpoint_3)) {
		Weakpoint_3->Destroy();
	}
	if (UKismetSystemLibrary::IsValid(Weakpoint_4)) {
		Weakpoint_4->Destroy();
	}
	Super::EndPlay(EndPlayReason);
}
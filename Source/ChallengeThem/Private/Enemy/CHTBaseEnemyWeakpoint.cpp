// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/CHTBaseEnemyWeakpoint.h"
#include"Enemy/CHTWeakpointCollision.h"
#include"Enemy/CHTBaseEnemy.h"
#include"PaperFlipbookComponent.h"
ACHTBaseEnemyWeakpoint::ACHTBaseEnemyWeakpoint() {
	WeakpointSprite = CreateDefaultSubobject<UPaperFlipbookComponent>("WeakpointSprite");
	SetRootComponent(WeakpointSprite);
	WeakpointCollision = CreateDefaultSubobject<UCHTWeakpointCollision>("WeakpointCollision");
	WeakpointCollision->SetupAttachment(GetRootComponent());
}
void ACHTBaseEnemyWeakpoint::BeginPlay() {
	Super::BeginPlay();
	OnWeakpointBreak.AddDynamic(OwningEnemy, &ACHTBaseEnemy::OnWeakpointBreak);
	auto CHTWeakpointCollision = Cast<UCHTWeakpointCollision>(WeakpointCollision);
	check(CHTWeakpointCollision);
	CHTWeakpointCollision->OnWeakpointHit.AddDynamic(this, &ACHTBaseEnemyWeakpoint::WeakpointHit);
}
void ACHTBaseEnemyWeakpoint::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
void ACHTBaseEnemyWeakpoint::SetOwningEnemy(ACHTBaseEnemy* TheOwningEnemy) {
	OwningEnemy = TheOwningEnemy;
}
void ACHTBaseEnemyWeakpoint::SetWeakpointIndex(int Index) {
	WeakpointIndex = Index;
}
void ACHTBaseEnemyWeakpoint::SetRemainingHitTimes(int Times) {
	RemainingHitTimes = Times;
}
ACHTBaseEnemy* ACHTBaseEnemyWeakpoint::GetOwningEnemy() const {
	return OwningEnemy;
}
int ACHTBaseEnemyWeakpoint::GetWeakpointIndex() const {
	return WeakpointIndex;
}
void ACHTBaseEnemyWeakpoint::WeakpointBreak() {
	SetLifeSpan(0.5f);
	OnWeakpointBreak.Broadcast(WeakpointIndex);
}
void ACHTBaseEnemyWeakpoint::WeakpointHit() {
	--RemainingHitTimes;
	if (RemainingHitTimes == 0)
		WeakpointBreak();
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/CHTBaseEnemy.h"
#include"Enemy/CHTBaseEnemyController.h"
#include"Enemy/CHTBaseEnemyWeakpoint.h"
#include"Kismet/GameplayStatics.h"
#include"Components/BoxComponent.h"
#include"PaperFlipbookComponent.h"
#include"GameBase/CHTGameInstance.h"
#include"Kismet/KismetSystemLibrary.h"
#include"PaperZDAnimationComponent.h"
#include"PaperZDAnimInstance.h"
#include"PaperFlipbookComponent.h"
#include"AIController.h"
ACHTBaseEnemy::ACHTBaseEnemy() {
	bUseControllerRotationPitch = bUseControllerRotationRoll = bUseControllerRotationYaw = false;
	AIControllerClass = ACHTBaseEnemyController::StaticClass();
	WeakpointLayer = CreateDefaultSubobject<UPaperFlipbookComponent>("WeakpointLayer");
	WeakpointLayer->SetupAttachment(GetSprite());
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AttackFXSprite = CreateDefaultSubobject<UPaperFlipbookComponent>("AttackFXSprite");
	AttackFXSprite->SetupAttachment(GetRootComponent());
	AttackCollision = CreateDefaultSubobject<UBoxComponent>("AttackCollision");
	AttackCollision->SetupAttachment(AttackFXSprite);
	AttackFXAnim = CreateDefaultSubobject<UPaperZDAnimationComponent>("AttackFXAnim");
	AttackFXAnim->InitRenderComponent(AttackFXSprite);
}
void ACHTBaseEnemy::BeginPlay() {
	Super::BeginPlay();
	SpawnWeakpoints();
	if (auto AC = Cast<AAIController>(GetController())) {
		AC->SetFocus(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	}
}
void ACHTBaseEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (IsAttacking || IsHurting || IsDead) return;
	float Yaw = GetControlRotation().Yaw;
	while (Yaw < 0 || Yaw>=360) {
		if (Yaw >= 360) Yaw -= 360;
		else Yaw += 360;
	}
	if (Yaw > 90 && Yaw < 270) {
		GetSprite()->SetRelativeScale3D(FVector(-1,1,1));
		FVector OldFXScale = AttackFXSprite->GetRelativeScale3D();
		FVector OldFXLocation = AttackFXSprite->GetRelativeLocation();
		if (OldFXScale.X >= 0) {
			OldFXScale.X = -OldFXScale.X;
			OldFXLocation.X = -OldFXLocation.X;
			AttackFXSprite->SetRelativeScale3D(OldFXScale);
			AttackFXSprite->SetRelativeLocation(OldFXLocation);
		}
	}
	else {
		GetSprite()->SetRelativeScale3D(FVector(1, 1, 1));
		FVector OldFXScale = AttackFXSprite->GetRelativeScale3D();
		FVector OldFXLocation = AttackFXSprite->GetRelativeLocation();
		if (OldFXScale.X < 0) {
			OldFXScale.X = -OldFXScale.X;
			OldFXLocation.X = -OldFXLocation.X;
			AttackFXSprite->SetRelativeScale3D(OldFXScale);
			AttackFXSprite->SetRelativeLocation(OldFXLocation);
		}

	}
}
void ACHTBaseEnemy::Reset() {
	Destroy();
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
void ACHTBaseEnemy::OnAttack() {
	if (IsHurting || IsDead) return;
	IsAttacking = true;
	Play2DMontage("JumpToAttack");
	if (auto CHTAnimInstance = AttackFXAnim->GetAnimInstance()) {
		CHTAnimInstance->JumpToNode("JumpToShowFX", "Montage");
	}
}
void ACHTBaseEnemy::CheckAttack() {
	TArray<AActor*> OverlappingActors;
	AttackCollision->GetOverlappingActors(OverlappingActors);
	if (AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) {
		for (auto OverlappingActor:OverlappingActors) {
			if (OverlappingActor == PlayerPawn)
			{
				UGameplayStatics::ApplyDamage(PlayerPawn, 1, GetController(), this, UDamageType::StaticClass());
			}
		}
	}
}
void ACHTBaseEnemy::OnAttackFinish() {
	IsAttacking = false;
}
void ACHTBaseEnemy::OnHurt()
{
	IsHurting = true;
	IsAttacking = false;
	Play2DMontage("JumpToHurt");
}
void ACHTBaseEnemy::OnHurtFinish()
{
	IsHurting = false;
}
void ACHTBaseEnemy::OnDead() {
	
	IsDead = true;
	IsAttacking = IsHurting = false;
	Play2DMontage("JumpToDead");
	if (auto EnemyController = Cast<ACHTBaseEnemyController>(GetController())) {
		EnemyController->OnEnemyDead();
	}
	SetLifeSpan(1.0f);
	OnEnemyDead.Broadcast();
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
		OnDead();
	}
	else {
		OnHurt();
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
void ACHTBaseEnemy::Play2DMontage(FName MontageName) {
	if (auto CHTAnimInstance = GetAnimationComponent()->GetAnimInstance()) {
		CHTAnimInstance->JumpToNode(MontageName, "Montage");
	}
}
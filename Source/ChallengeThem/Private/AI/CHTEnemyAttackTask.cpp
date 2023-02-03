// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CHTEnemyAttackTask.h"
#include"Enemy/CHTBaseEnemy.h"
#include"AIController.h"
#include"Kismet/GameplayStatics.h"
EBTNodeResult::Type UCHTEnemyAttackTask::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

	auto AC = OwnerComp.GetAIOwner();
	if (!AC) return EBTNodeResult::Failed;
	auto CHTEnemy = Cast<ACHTBaseEnemy>(AC->GetPawn());
	if (auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0)) {
		FVector2D Dis;
		Dis.X = PlayerPawn->GetActorLocation().X - CHTEnemy->GetActorLocation().X;
		Dis.Y = PlayerPawn->GetActorLocation().Y - CHTEnemy->GetActorLocation().Y;
		if (Dis.Length()<=AttackRange) {
			CHTEnemy->OnAttack();
			return EBTNodeResult::Succeeded;
		}
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}

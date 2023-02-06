// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/CHTBaseEnemyController.h"
#include"Enemy/CHTBaseEnemy.h"
#include"BrainComponent.h"
ACHTBaseEnemyController::ACHTBaseEnemyController() {

}
void ACHTBaseEnemyController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
}
void ACHTBaseEnemyController::Wakeup() {
	if (auto Enemy = Cast<ACHTBaseEnemy>(GetPawn())) {
		if (Enemy->BehaviorTreeAsset) {
			RunBehaviorTree(Enemy->BehaviorTreeAsset);
		}
	}
}
void ACHTBaseEnemyController::OnEnemyDead() {
	if (auto Brain = GetBrainComponent()) {
		Brain->Cleanup();
	}
}


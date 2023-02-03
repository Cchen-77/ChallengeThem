// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CHTEnemyAttackTask.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGETHEM_API UCHTEnemyAttackTask : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
protected:
	UPROPERTY(EditAnywhere, Category = Detail)
		float AttackRange = 50.0f;
};

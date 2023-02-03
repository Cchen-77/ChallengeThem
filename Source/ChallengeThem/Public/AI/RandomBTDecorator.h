// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RandomBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGETHEM_API URandomBTDecorator : public UBTDecorator
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = Detail)
		float Posibility = 1.0;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};

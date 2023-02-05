// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RandomBTDecorator.h"
bool URandomBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	return FMath::RandRange(0, 1) <= Posibility;
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "CHTWeakpointCollision.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeakpointHitSignature);
UCLASS()
class CHALLENGETHEM_API UCHTWeakpointCollision : public UBoxComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
		FWeakpointHitSignature OnWeakpointHit;
	UFUNCTION()
		void BeHit();
};

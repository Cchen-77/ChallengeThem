// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CHTBaseEnemyWeakpoint.generated.h"

/**
 * 
 */
class UBoxComponent;
class ACHTBaseEnemy;
class UPaperFlipbookComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeakpointBreakSignature, int, WeakpointIndex);
UCLASS()
class CHALLENGETHEM_API ACHTBaseEnemyWeakpoint : public AActor
{
	GENERATED_BODY()
public:
	ACHTBaseEnemyWeakpoint();
	
	UFUNCTION()
		void WeakpointHit();
	UFUNCTION(BlueprintCallable)
		void WeakpointBreak();
	UPROPERTY(BlueprintAssignable)
		FWeakpointBreakSignature OnWeakpointBreak;
	virtual void Tick(float DeltaTime) override;
	void SetOwningEnemy(ACHTBaseEnemy* TheOwningEnemy);
	ACHTBaseEnemy* GetOwningEnemy() const;
	void SetWeakpointIndex(int Index);
	int GetWeakpointIndex() const;
	void SetRemainingHitTimes(int Times);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UPaperFlipbookComponent* WeakpointSprite;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UBoxComponent* WeakpointCollision;
	int WeakpointIndex = 0.0f;
	virtual void BeginPlay() override;
	ACHTBaseEnemy* OwningEnemy;

	int RemainingHitTimes = 1;
	
};

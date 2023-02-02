// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TopDownCharacter.h"
#include"GameBase/CHTResetInterface.h"
#include "CHTBaseEnemy.generated.h"

/**
 * 
 */
class ACHTBaseEnemyWeakpoint;
class UPaperFlipbookComponet;
class UBehaviorTree;
UCLASS()
class CHALLENGETHEM_API ACHTBaseEnemy : public ATopDownCharacter,public ICHTResetInterface
{
	GENERATED_BODY()
public:
	ACHTBaseEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void Reset() override;
	UFUNCTION(BlueprintCallable)
		void SpawnWeakpoints();
	UFUNCTION()
		virtual void OnWeakpointBreak(int WeakpointIndex);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI)
		UBehaviorTree* BehaviorTreeAsset;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weakpoint)
		UPaperFlipbookComponent* WeakpointLayer;
	UPROPERTY(EditDefaultsOnly, Category = Weakpoint)
		TSubclassOf<ACHTBaseEnemyWeakpoint> WeakpointClass;
	UPROPERTY(EditDefaultsOnly, Category = Weakpoint)
		int MAXWeakpointHitTimes = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weakpoint)
		bool HavWeakpoint_1 = true;
	UPROPERTY()
		ACHTBaseEnemyWeakpoint* Weakpoint_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weakpoint)
		bool HavWeakpoint_2 = true;
	UPROPERTY()
		ACHTBaseEnemyWeakpoint* Weakpoint_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weakpoint)
		bool HavWeakpoint_3 = true;
	UPROPERTY()
		ACHTBaseEnemyWeakpoint* Weakpoint_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weakpoint)
		bool HavWeakpoint_4 = true;
	UPROPERTY()
		ACHTBaseEnemyWeakpoint* Weakpoint_4;
	ACHTBaseEnemyWeakpoint* SpawnWeakpoint(int WeakpointIndex,bool HavWeakpoint);
	int WeakpointCount = 0;

	UFUNCTION(BlueprintCallable)
		void OnAttack();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Actions)
		bool IsAttacking = false;
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void InAttacking();
	UFUNCTION(BlueprintCallable)
		void OnAttackFinish();

	UFUNCTION(BlueprintCallable)
		void OnHurt();
	UFUNCTION(BlueprintCallable)
		void OnHurtFinish();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Actions)
		bool IsHurting = false;

	UFUNCTION(BlueprintCallable)
		void OnDead();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Actions)
		bool IsDead = false;

	void Play2DMontage(FName MontageName);
};

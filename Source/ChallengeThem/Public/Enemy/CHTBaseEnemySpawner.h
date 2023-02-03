// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"GameBase/CHTResetInterface.h"
#include "CHTBaseEnemySpawner.generated.h"
class ACHTBaseEnemy;
class UBoxComponent;
USTRUCT(BlueprintType)
struct FEnemyInfo {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = EnemyInfo)
		TSubclassOf<ACHTBaseEnemy> EnemyClass;
	UPROPERTY(EditAnywhere, Category = EnemyInfo)
		FVector EnemyLocation;
};
UCLASS()
class CHALLENGETHEM_API ACHTBaseEnemySpawner : public AActor, public ICHTResetInterface
{
	GENERATED_BODY()
	
public:	
	ACHTBaseEnemySpawner();
	virtual void Tick(float DeltaTime) override;
	virtual void Reset() override;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemys)
		TArray<FEnemyInfo> EnemyInfos;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enemys)
		UBoxComponent* SpawnerCollision;
	bool Touched = false;
	UFUNCTION()
		void BeTouched(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor,
			UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void StartSpawn();
	int EnemyCounter = 0;
	void OnEnemyDead();
	void OnAllEnemyDead();
};

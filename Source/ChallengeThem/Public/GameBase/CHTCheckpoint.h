// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CHTCheckpoint.generated.h"
class UBoxComponent;
UCLASS()
class CHALLENGETHEM_API ACHTCheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ACHTCheckpoint();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Compnents)
		UBoxComponent* CheckpointCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Checkpoint)
		int CheckpointIndex = 0;
	UFUNCTION()
		void ActorOverlapCheckpoint(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	bool Checked = false;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishBox.generated.h"

class UBoxComponent;
UCLASS()
class CHALLENGETHEM_API AFinishBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AFinishBox();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
		UBoxComponent* Collision;
	virtual void BeginPlay() override;
	UFUNCTION()
	void BeTouched(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};

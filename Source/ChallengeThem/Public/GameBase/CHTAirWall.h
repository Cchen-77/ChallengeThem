// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CHTAirWall.generated.h"
class UBoxComponent;
UCLASS()
class CHALLENGETHEM_API ACHTAirWall : public AActor
{
	GENERATED_BODY()
	
public:	
	ACHTAirWall();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UBoxComponent* WallCollision;
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

};

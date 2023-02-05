// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"GameBase/CHTResetInterface.h"
#include "DialogBox.generated.h"
class UBoxComponent;
UCLASS()
class CHALLENGETHEM_API ADialogBox : public AActor,public ICHTResetInterface
{
	GENERATED_BODY()
	
public:
	ADialogBox();
protected:
	virtual void Reset() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
		UBoxComponent* Collision;
	virtual void BeginPlay() override;
	UFUNCTION()
		void BeTouched(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog)
		TArray<FString> Texts;
	bool Touched = false;
};

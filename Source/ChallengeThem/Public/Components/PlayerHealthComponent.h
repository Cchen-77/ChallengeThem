// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDeadSignature);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHALLENGETHEM_API UPlayerHealthComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UPlayerHealthComponent();
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	void TakeHealing(float  Amount);
	float GetHealth() const;
	UPROPERTY(BlueprintAssignable)
		FPlayerDeadSignature OnPlayerDead;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = Health)
		float DefaultHealth = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Health)
		float Health = 0.0f;
	
};
#include "Components/PlayerHealthComponent.h"
UPlayerHealthComponent::UPlayerHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}
void UPlayerHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = DefaultHealth;
}
float UPlayerHealthComponent::GetHealth() const {
	return Health;
}
void UPlayerHealthComponent::TakeDamage(AActor* DamagedActor, float Damage,const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) {
	Health = FMath::Clamp<float>(Health - Damage, 0.0f, DefaultHealth);
	if (Health == 0)
		OnPlayerDead.Broadcast();
}
void UPlayerHealthComponent::TakeHealing(float Amount) {
	if (Health == 0) return;
	Health = FMath::Clamp<float>(Health + Amount, 0.0f, DefaultHealth);
}



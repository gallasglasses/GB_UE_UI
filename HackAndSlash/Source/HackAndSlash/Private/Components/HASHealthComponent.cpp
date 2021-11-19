// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/HASHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All);

UHASHealthComponent::UHASHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float UHASHealthComponent::GetHealth() const
{
	return Health;
}

bool UHASHealthComponent::IsDead() const
{
	return Health <= 0.0f;
}

void UHASHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHASHealthComponent::OnTakeAnyDamage);
	}
}

void UHASHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead())
	{
		return;
	}
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

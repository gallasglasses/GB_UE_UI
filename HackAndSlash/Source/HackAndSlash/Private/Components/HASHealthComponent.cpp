// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/HASHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All);

UHASHealthComponent::UHASHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float UHASHealthComponent::GetHealthPercent() const
{
	return Health / MaxHealth;
}

float UHASHealthComponent::GetHealth() const
{
	return Health;
}

bool UHASHealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsDead() || IsHealthFull())
	{
		return false;
	}
	SetHealth(Health + HealthAmount);
	return true;
}

bool UHASHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

bool UHASHealthComponent::IsDead() const
{
	return FMath::IsNearlyZero(Health);
}

void UHASHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHASHealthComponent::OnTakeAnyDamage);
	}
}

void UHASHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld())
	{
		return;
	}
	SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UHASHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}
}

void UHASHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);

	if (IsHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void UHASHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;

	UE_LOG(HealthComponentLog, Display, TEXT("Delta %f Health %f NextHealth %f"), HealthDelta, Health, NextHealth);
	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

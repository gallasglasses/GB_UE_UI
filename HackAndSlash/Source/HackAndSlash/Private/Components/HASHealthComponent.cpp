// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/HASHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Dev/HASIceDamageType.h"
#include "Dev/HASFireDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All);

UHASHealthComponent::UHASHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float UHASHealthComponent::GetHealth() const
{
	return Health;
}

void UHASHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHASHealthComponent::OnTakeAnyDamage);
	}
}

void UHASHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	UE_LOG(HealthComponentLog, Display, TEXT("Damage : %f"), Damage);

	if (DamageType)
	{
		if (DamageType->IsA<UHASFireDamageType>())
		{
			UE_LOG(HealthComponentLog, Display, TEXT("So hoooot!"));
		}
		else if (DamageType->IsA<UHASIceDamageType>())
		{
			UE_LOG(HealthComponentLog, Display, TEXT("So cooold!"));
		}
	}
}
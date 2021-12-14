// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/HASHealthPickup.h"
#include "Components/HASHealthComponent.h"
#include "HASUtils.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

AHASHealthPickup::AHASHealthPickup()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->IgnoreActorWhenMoving(GetOwner(), true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

bool AHASHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	//UE_LOG(LogHealthPickup, Display, TEXT("Health was taken"));
	const auto HealthComponent = HASUtils::GetHASPlayerComponent<UHASHealthComponent>(PlayerPawn);
	if (!HealthComponent)
	{
		return false;
	}
	return HealthComponent->TryToAddHealth(HealthAmount);
}
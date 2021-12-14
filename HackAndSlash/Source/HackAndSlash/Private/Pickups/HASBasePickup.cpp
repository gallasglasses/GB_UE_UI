// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/HASBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

AHASBasePickup::AHASBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

void AHASBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
	check(CollisionComponent);
}

void AHASBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(Pawn))
	{
		PickupWasTaken();
	}
}

void AHASBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AHASBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void AHASBasePickup::PickupWasTaken()
{
	Destroy();
	UE_LOG(LogBasePickup, Display, TEXT("Pickup was destroy"));
}
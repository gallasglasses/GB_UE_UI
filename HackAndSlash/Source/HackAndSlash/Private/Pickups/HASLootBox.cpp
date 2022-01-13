// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/HASLootBox.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HASInventoryComponent.h"
#include "HASInventoryManagerComponent.h"
#include "HASInventoryData.h"
#include "HASUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogLootBox, All, All);

AHASLootBox::AHASLootBox()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);

	CloseLootBoxComponent = CreateDefaultSubobject<UStaticMeshComponent>("CloseLootBoxComponent");
	CloseLootBoxComponent->SetupAttachment(RootComponent);

	OpenLootBoxComponent = CreateDefaultSubobject<UStaticMeshComponent>("OpenLootBoxComponent");
	OpenLootBoxComponent->SetupAttachment(RootComponent);
	OpenLootBoxComponent->SetHiddenInGame(true);

	InventoryComponent = CreateDefaultSubobject<UHASInventoryComponent>("InventoryComponent");
	InventoryManagerComponent = CreateDefaultSubobject<UHASInventoryManagerComponent>("InventoryManagerComponent");

}

void AHASLootBox::BeginPlay()
{
	Super::BeginPlay();
	
	check(CollisionComponent);
	check(InventoryComponent);
	check(InventoryManagerComponent);

	if (DefaultLootPack)
	{
		TArray<FInventorySlotInfo*> SlotInfo;
		DefaultLootPack->GetAllRows<FInventorySlotInfo>("", SlotInfo);
		for (int32 i = 0; i < SlotInfo.Num(); i++)
		{
			InventoryComponent->SetItem(i, *SlotInfo[i]);
		}
	}
}

//void AHASLootBox::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	Super::NotifyActorBeginOverlap(OtherActor);
//
//	UE_LOG(LogLootBox, Display, TEXT("LootBox is here"));
//	const auto Pawn = Cast<APawn>(OtherActor);
//	if (GivePickupTo(Pawn))
//	{
//		UE_LOG(LogLootBox, Display, TEXT("LootBox is open"));
//	}
//}

void AHASLootBox::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);

	const auto PlayerInventoryManagerComponent = HASUtils::GetHASPlayerComponent<UHASInventoryManagerComponent>(Pawn);
	if (!PlayerInventoryManagerComponent)
	{
		return;
	}
	else
	{
		const auto PlayerInventoryComponent = HASUtils::GetHASPlayerComponent<UHASInventoryComponent>(Pawn);
		if (!PlayerInventoryComponent)
		{
			return;
		}
		PlayerInventoryManagerComponent->RemoveInventory();
	}
	if (InventoryManagerComponent && InventoryComponent)
	{ 
		InventoryManagerComponent->RemoveInventory();
	}

	CloseLootBoxComponent->SetHiddenInGame(false);//
	OpenLootBoxComponent->SetHiddenInGame(true);//
	bIsOpen = false;//

	PickupWasTaken();
	UE_LOG(LogLootBox, Display, TEXT("LootBox is not here"));
}

void AHASLootBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AHASLootBox::GivePickupTo(/*APawn* PlayerPawn*/)
{
	const auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();//
	const auto PlayerInventoryManagerComponent = HASUtils::GetHASPlayerComponent<UHASInventoryManagerComponent>(PlayerPawn);
	if (!PlayerInventoryManagerComponent)
	{
		return false;
	}
	const auto PlayerInventoryComponent = HASUtils::GetHASPlayerComponent<UHASInventoryComponent>(PlayerPawn);
	if (!PlayerInventoryComponent)
	{
		return false;
	}
	CloseLootBoxComponent->SetHiddenInGame(true);
	OpenLootBoxComponent->SetHiddenInGame(false);
	bIsOpen = true;
	PlayerInventoryManagerComponent->Init(PlayerInventoryComponent);
	if (!InventoryManagerComponent && !InventoryComponent)
	{
		return false;
	}
	InventoryManagerComponent->Init(InventoryComponent);
	return true;
}

void AHASLootBox::PickupWasTaken()
{
	if (InventoryComponent->GetItemsNum() == 0)
	{
		Destroy();
		UE_LOG(LogLootBox, Display, TEXT("LootBox taken"));
	}
}

void AHASLootBox::EndPickupTo()
{
	const auto Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	const auto PlayerInventoryManagerComponent = HASUtils::GetHASPlayerComponent<UHASInventoryManagerComponent>(Pawn);
	if (!PlayerInventoryManagerComponent)
	{
		return;
	}
	else
	{
		const auto PlayerInventoryComponent = HASUtils::GetHASPlayerComponent<UHASInventoryComponent>(Pawn);
		if (!PlayerInventoryComponent)
		{
			return;
		}
		PlayerInventoryManagerComponent->RemoveInventory();
	}
	InventoryManagerComponent->RemoveInventory();
	CloseLootBoxComponent->SetHiddenInGame(false);
	OpenLootBoxComponent->SetHiddenInGame(true);
	bIsOpen = false;
	PickupWasTaken();
	UE_LOG(LogLootBox, Display, TEXT("LootBox is not here"));
}
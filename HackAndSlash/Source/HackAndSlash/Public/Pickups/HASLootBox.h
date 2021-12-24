// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HASLootBox.generated.h"

class USphereComponent;
class UHASInventoryComponent;
class UHASInventoryManagerComponent;
class UDataTable;
class UStaticMeshComponent;

UCLASS()
class HACKANDSLASH_API AHASLootBox : public AActor
{
	GENERATED_BODY()
	
public:
	AHASLootBox();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WeaponryComponents")
	UStaticMeshComponent* LootBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHASInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHASInventoryManagerComponent* InventoryManagerComponent;

	UPROPERTY(EditAnywhere, Category = "LootPack")
	UDataTable* DefaultLootPack;

	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn);
	void PickupWasTaken();
};

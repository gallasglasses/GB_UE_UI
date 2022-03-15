// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaveSystem/SaveData.h"
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
	UStaticMeshComponent* CloseLootBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* OpenLootBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHASInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHASInventoryManagerComponent* InventoryManagerComponent;

	UPROPERTY(EditAnywhere, Category = "LootPack")
	UDataTable* DefaultLootPack;

	FLootSaveData SaveData;

	virtual void BeginPlay() override;
	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:
	virtual void Tick(float DeltaTime) override;

//private:
	UFUNCTION(BlueprintCallable)
	virtual bool GivePickupTo(/*APawn* PlayerPawn*/);

	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
		FLootSaveData GetLootData();

	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
		void SetLootData(FLootSaveData SavedData);

	UFUNCTION(BlueprintCallable)
	void PickupWasTaken();

	UFUNCTION(BlueprintCallable)
	void EndPickupTo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootBox")
	bool bIsOpen = false;
};

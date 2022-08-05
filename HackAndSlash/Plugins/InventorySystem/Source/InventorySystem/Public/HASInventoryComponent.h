// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HASInventoryData.h"
#include "HASInventoryComponent.generated.h"

// struct FInventorySlotInfo;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UHASInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		TMap<int32, FInventorySlotInfo> Items;

	UPROPERTY(EditDefaultsOnly)
		TMap<int32, FInventorySlotInfo> ItemsOfSameType;

public:

	const FInventorySlotInfo* GetItem(int32 SlotIndex) const;
	const FInventorySlotInfo* GetItemOfSameType(int32 SlotIndex) const;

	virtual void SetItem(int32 SlotIndex, const FInventorySlotInfo& Item);
	virtual void ClearItem(int32 SlotIndex);
	virtual void ChangeKeyItem(const FInventorySlotInfo& ItemFrom, const int32 IndexFrom, const FInventorySlotInfo& ItemTo, const int32 IndexTo);
	virtual void Serialize(FArchive& Ar);

	void SetItemOfSameType(int32 SlotIndex, const FInventorySlotInfo& Item);
	void ClearItems();
	void ClearItemsOfSameType();

	const TMap<int32, FInventorySlotInfo>& GetItems() const;
	const TMap<int32, FInventorySlotInfo>& GetItemsOfSameType() const;

	virtual int32 GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& InItem);

	int32 GetItemsNum() const;
	int32 GetItemsOfSameTypeNum() const;

};
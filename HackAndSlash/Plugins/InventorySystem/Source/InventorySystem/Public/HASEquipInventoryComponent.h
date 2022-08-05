// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HASInventoryComponent.h"
#include "HASEquipInventoryComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UHASEquipInventoryComponent : public UHASInventoryComponent
{
	GENERATED_BODY()

public:

	UHASEquipInventoryComponent();

	UPROPERTY(EditAnywhere)
		TMap<int32, EEquipSlot> EquipSlots;

	virtual int32 GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& InItem) override;

	virtual void SetItem(int32 SlotIndex, const FInventorySlotInfo& Item) override;

	virtual void ClearItem(int32 SlotIndex) override;

	virtual void ChangeKeyItem(const FInventorySlotInfo& ItemFrom, const int32 IndexFrom, const FInventorySlotInfo& ItemTo, const int32 IndexTo) override;
	
	virtual void Serialize(FArchive& Ar);
};
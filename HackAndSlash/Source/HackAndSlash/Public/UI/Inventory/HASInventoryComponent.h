// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UI/Inventory/HASInventoryData.h"
#include "HASInventoryComponent.generated.h"

// struct FInventorySlotInfo;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKANDSLASH_API UHASInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TMap<int32, FInventorySlotInfo> Items;
		
public:

	const FInventorySlotInfo* GetItem(int32 SlotIndex) const;

	virtual void SetItem(int32 SlotIndex, const FInventorySlotInfo& Item);
	virtual void ClearItem(int32 SlotIndex);

	void ChangeKeyItem(const FInventorySlotInfo& ItemFrom, const int32 IndexFrom, const FInventorySlotInfo& ItemTo, const int32 IndexTo);

	const TMap<int32, FInventorySlotInfo>& GetItems() const;

	int32 GetItemsNum() const;

};

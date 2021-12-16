// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/HASInventoryComponent.h"

const FInventorySlotInfo* UHASInventoryComponent::GetItem(int32 SlotIndex) const
{
	return Items.Find(SlotIndex);
}

void UHASInventoryComponent::SetItem(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	ClearItem(SlotIndex);

	Items.Add(SlotIndex, Item);
}

void UHASInventoryComponent::ClearItem(int32 SlotIndex)
{
	Items.Remove(SlotIndex);
}

const TMap<int32, FInventorySlotInfo>& UHASInventoryComponent::GetItems() const
{
	return Items;
}

int32 UHASInventoryComponent::GetItemsNum() const
{
	return Items.Num();
}

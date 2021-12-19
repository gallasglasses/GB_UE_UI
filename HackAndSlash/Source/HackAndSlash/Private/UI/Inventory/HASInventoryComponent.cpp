// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/HASInventoryComponent.h"

const FInventorySlotInfo* UHASInventoryComponent::GetItem(int32 SlotIndex) const
{
	return Items.Find(SlotIndex);
}

const FInventorySlotInfo* UHASInventoryComponent::GetItemOfSameType(int32 SlotIndex) const
{
	return ItemsOfSameType.Find(SlotIndex);
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

const TMap<int32, FInventorySlotInfo>& UHASInventoryComponent::GetItemsOfSameType() const
{
	return ItemsOfSameType;
}

int32 UHASInventoryComponent::GetItemsNum() const
{
	return Items.Num();
}

int32 UHASInventoryComponent::GetItemsOfSameTypeNum() const
{
	return ItemsOfSameType.Num();
}

void UHASInventoryComponent::SetItemOfSameType(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	ItemsOfSameType.Add(SlotIndex, Item);
}

void UHASInventoryComponent::ChangeKeyItem(const FInventorySlotInfo& ItemFrom, const int32 IndexFrom, const FInventorySlotInfo& ItemTo, const int32 IndexTo)
{
	const FInventorySlotInfo* FindItem = GetItem(IndexFrom);
	if ((*FindItem).ID == ItemFrom.ID && (*FindItem).Count == ItemFrom.Count)
	{
		
		if (ItemTo.ID.IsNone())
		{
			ClearItem(IndexFrom);
			Items.Add(IndexTo, ItemFrom);
		}
		else 
		{
			FindItem = GetItem(IndexTo);
			if ((*FindItem).ID == ItemTo.ID && (*FindItem).Count == ItemTo.Count)
			{
				SetItem(IndexFrom, ItemTo);
				SetItem(IndexTo, ItemFrom);
			}
		}
	}
}

void UHASInventoryComponent::ClearItemsOfSameType()
{
	for (int32 i = 0; i <= ItemsOfSameType.Num(); i++)
	{
		ItemsOfSameType.Remove(i);
	}
}

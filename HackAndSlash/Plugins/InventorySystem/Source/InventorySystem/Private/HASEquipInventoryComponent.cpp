// Fill out your copyright notice in the Description page of Project Settings.


#include "HASEquipInventoryComponent.h"
#include "HASEquipInterface.h"

UHASEquipInventoryComponent::UHASEquipInventoryComponent()
{
	EquipSlots.Add(0, EEquipSlot::ES_RightHandWeaponry);
	EquipSlots.Add(1, EEquipSlot::ES_LeftHandWeaponry);
	EquipSlots.Add(2, EEquipSlot::ES_AddRightHandWeaponry);
	EquipSlots.Add(3, EEquipSlot::ES_AddLeftHandWeaponry);
	EquipSlots.Add(4, EEquipSlot::ES_HeadEquip);
	EquipSlots.Add(5, EEquipSlot::ES_ArmsEquip);
	EquipSlots.Add(6, EEquipSlot::ES_BodyEquip);
	EquipSlots.Add(7, EEquipSlot::ES_LegsEquip);
	EquipSlots.Add(8, EEquipSlot::ES_FeetEquip);
}

int32 UHASEquipInventoryComponent::GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& InItem)
{
	EEquipSlot* EquipSlotPtr = EquipSlots.Find(SlotIndex);
	if (InItem.Type == EItemType::IT_Equipment && *EquipSlotPtr == InItem.Equip && EquipSlotPtr && InItem.Equip == EquipSlots.FindChecked(SlotIndex))
	{
		return 1;
	}
	return 0;
}

void UHASEquipInventoryComponent::SetItem(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	auto* InventoryOwner = GetOwner();

	if (!InventoryOwner->GetClass()->ImplementsInterface(UHASEquipInterface::StaticClass()))
	{
		Super::SetItem(SlotIndex, Item);
		return;
	}

	const FInventorySlotInfo* EquippedItemInfo = GetItem(SlotIndex);
	EEquipSlot Equip = EquipSlots.Contains(SlotIndex) ? EquipSlots.FindChecked(SlotIndex) : EEquipSlot::ES_None;

	if (EquippedItemInfo)
	{
		IHASEquipInterface::Execute_UnequipItem(InventoryOwner, Equip, EquippedItemInfo->ID);
	}

	Super::SetItem(SlotIndex, Item);
	IHASEquipInterface::Execute_EquipItem(InventoryOwner, Equip, Item.ID);
}

void UHASEquipInventoryComponent::ClearItem(int32 SlotIndex)
{
	auto* InventoryOwner = GetOwner();

	if (!InventoryOwner->GetClass()->ImplementsInterface(UHASEquipInterface::StaticClass()))
	{
		Super::ClearItem(SlotIndex);
		return;
	}

	const FInventorySlotInfo* EquippedItemInfo = GetItem(SlotIndex);
	EEquipSlot Equip = EquipSlots.FindChecked(SlotIndex);

	if (EquippedItemInfo)
	{
		IHASEquipInterface::Execute_UnequipItem(InventoryOwner, Equip, EquippedItemInfo->ID);
	}

	Super::ClearItem(SlotIndex);
}

void UHASEquipInventoryComponent::ChangeKeyItem(const FInventorySlotInfo& ItemFrom, const int32 IndexFrom, const FInventorySlotInfo& ItemTo, const int32 IndexTo)
{
	return;
}
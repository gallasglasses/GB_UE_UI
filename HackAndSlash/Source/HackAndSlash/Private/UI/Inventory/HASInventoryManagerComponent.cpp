// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/HASInventoryManagerComponent.h"
#include "UI/Inventory/HASEquipInventoryComponent.h"
#include "UI/Inventory/HASInventoryComponent.h"
#include "UI/Inventory/HASInventoryCellWidget.h"
#include "UI/Inventory/HASInventoryWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogInventoryManagerComponent, All, All);

UHASInventoryManagerComponent::UHASInventoryManagerComponent()
{
	// ...
}

void UHASInventoryManagerComponent::Init(UHASInventoryComponent* InInventoryComponent)
{
	LocalInventoryComponent = InInventoryComponent;
	if (LocalInventoryComponent && ItemsData && InventoryWidgetClass)
	{
		//ensure(InventoryWidgetClass);
		InventoryWidget = CreateWidget<UHASInventoryWidget>(GetWorld(), InventoryWidgetClass);

		InventoryWidget->AddToViewport();
		InventoryWidget->ParentInventory = InInventoryComponent;

		InventoryWidget->Init(FMath::Max(LocalInventoryComponent->GetItemsNum(), MinInventorySize));

		InventoryWidget->OnItemDrop.AddUObject(this, &UHASInventoryManagerComponent::OnItemDropped);

		InventoryWidget->OnItemClick.AddUObject(this, &UHASInventoryManagerComponent::OnItemClicked);
		for (const auto& Item : LocalInventoryComponent->GetItems())
		{
			FInventoryItemInfo* ItemInfo = GetItemData(Item.Value.ID);
			if (ItemInfo)
			{
				//GLog->Log(ELogVerbosity::Warning,*FString::Printf(TEXT("Item %s, count %d"),ItemData->Name.ToString(),Item.Value.Count));

				//FString ItemDataStr = ItemData->Name.ToString() + ": " + FString::FromInt(Item.Value.Count);
				//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, ItemDataStr);

				ItemInfo->Icon.LoadSynchronous();
				InventoryWidget->AddItem(Item.Value, *ItemInfo, Item.Key);
			}
		}
		InventoryWidget->OnUpdateCells.AddUObject(this, &UHASInventoryManagerComponent::OnUpdateCells);
	}
}

FInventoryItemInfo* UHASInventoryManagerComponent::GetItemData(const FName& InID) const
{
	return ItemsData ? ItemsData->FindRow<FInventoryItemInfo>(InID,"") : nullptr;
}

void UHASInventoryManagerComponent::RemoveInventory()
{
	InventoryWidget->RemoveFromParent();
}

void UHASInventoryManagerComponent::RemoveEquip()
{

	EquipWidget->RemoveFromParent();
}

void UHASInventoryManagerComponent::OnItemDropped(UHASInventoryCellWidget* DraggedFrom, UHASInventoryCellWidget* DroppedTo)
{
	if (DraggedFrom == nullptr || DroppedTo == nullptr)
	{
		return;
	}

	auto* FromInventory = DraggedFrom->GetParentInventoryWidget();
	auto* ToInventory = DroppedTo->GetParentInventoryWidget();

	if (FromInventory == nullptr || ToInventory == nullptr)
	{
		return;
	}

	const FInventorySlotInfo FromItem = DraggedFrom->GetItem();
	if (FromItem.Count <= 0)
	{
		return;
	}
	const FInventorySlotInfo ToItem = DroppedTo->GetItem();

	FInventorySlotInfo NewFromItem = ToItem;
	FInventorySlotInfo NewToItem = FromItem;

	const FInventoryItemInfo* FromItemInfo = GetItemData(FromItem.ID);
	//const FInventoryItemInfo* ToItemInfo = ToItem.Count > 0 ? GetItemData(ToItem.ID) : nullptr;

	const int32 ToItemAmount = ToInventory->GetMaxItemAmount(DroppedTo->IndexInInventory, *FromItemInfo);
	 if (FromInventory != ToInventory)
	 {
 		if (ToItemAmount == 0)
 		{
 			return;
 		}

		if (ToItemAmount > 0)
		{
			NewToItem.Count = FMath::Max(ToItemAmount, FromItem.Count);
			if (FromItem.Count <= NewToItem.Count)
			{
				NewFromItem.ID = NewToItem.ID;
				NewFromItem.Count = FromItem.Count - NewToItem.Count;
			}
		}
	}

	const FInventoryItemInfo* NewFromItemInfo = NewFromItem.Count > 0 ? GetItemData(NewFromItem.ID) : nullptr;
	const FInventoryItemInfo* NewToItemInfo = GetItemData(NewToItem.ID);

	if (Cast<UHASEquipInventoryComponent>(DraggedFrom->GetParentInventoryWidget()) && Cast<UHASEquipInventoryComponent>(DroppedTo->GetParentInventoryWidget()))
	{
		return;
	}

	DroppedTo->Clear();
	DraggedFrom->Clear();

	if (NewFromItemInfo)
	{
		DraggedFrom->AddItem(NewFromItem, *NewFromItemInfo);
	}
	DroppedTo->AddItem(NewToItem, *NewToItemInfo);

	if (FromInventory == ToInventory)
	{
		FromInventory->ChangeKeyItem(FromItem, DraggedFrom->IndexInInventory, ToItem, DroppedTo->IndexInInventory);
	}
	if (NewFromItem.Count > 0)
	{
		FromInventory->SetItem(DraggedFrom->IndexInInventory, NewFromItem);
	}
	else
	{
		FromInventory->ClearItem(DraggedFrom->IndexInInventory);
	}
	ToInventory->SetItem(DroppedTo->IndexInInventory, NewToItem);
}

void UHASInventoryManagerComponent::ChangeKeyItem(const FInventorySlotInfo& FromItemDropped, const int32 FromIndexDropped, const FInventorySlotInfo& ToItemDropped, const int32 ToIndexDropped)
{
	LocalInventoryComponent->ChangeKeyItem(FromItemDropped, FromIndexDropped, ToItemDropped, ToIndexDropped);
}

void UHASInventoryManagerComponent::OnUpdateCells(EItemType ItemType)
{
	SwitchInventoryWidgetTabs(ItemType);
}

void UHASInventoryManagerComponent::OnItemClicked(UHASInventoryCellWidget* OnItemClickCell)
{
	if (OnItemClickCell == nullptr)
	{
		return;
	}

	auto* ClickInventory = OnItemClickCell->GetParentInventoryWidget();

	if (ClickInventory == nullptr)
	{
		return;
	}

	const FInventorySlotInfo& ClickedItem = OnItemClickCell->GetItem();

	UE_LOG(LogInventoryManagerComponent, Display, TEXT("Amount %d"), ClickedItem.Count);

 	if (ClickedItem.Count <= 0)
 	{
 		return;
 	}

	const FInventoryItemInfo* ClickedItemInfo = GetItemData(ClickedItem.ID);

	if ((*ClickedItemInfo).Type != EItemType::IT_Food)
	{
		return;
	}
	UE_LOG(LogInventoryManagerComponent, Display, TEXT("Item is FOOD!"));

	FInventorySlotInfo NewClickedItem = ClickedItem;
	const int32 ToItemAmount = ClickInventory->GetMaxItemAmount(OnItemClickCell->IndexInInventory, *ClickedItemInfo);
	
	if (ToItemAmount == 0)
	{
		return;
	}

	if (ToItemAmount < 0)
	{
		NewClickedItem.Count = ClickedItem.Count - 1;
		OnItemUse.Broadcast(ClickedItem.ID);
		UE_LOG(LogInventoryManagerComponent, Display, TEXT("Amount %d"), NewClickedItem.Count);
	}

	const FInventoryItemInfo* NewClickedItemInfo = NewClickedItem.Count > 0 ? GetItemData(NewClickedItem.ID) : nullptr;

	OnItemClickCell->Clear();
	if (NewClickedItemInfo)
	{
		OnItemClickCell->AddItem(NewClickedItem, *NewClickedItemInfo);
	}
	if (NewClickedItem.Count > 0)
	{
		ClickInventory->SetItem(OnItemClickCell->IndexInInventory, NewClickedItem);
	}
	else
	{
		ClickInventory->ClearItem(OnItemClickCell->IndexInInventory);
	}
}

void UHASInventoryManagerComponent::SwitchInventoryWidgetTabs(EItemType ItemType)
{
	if (LocalInventoryComponent && InventoryWidget)
	{
		LocalInventoryComponent->ClearItemsOfSameType();		
		InventoryWidget->ClearItems();

		int32 CountIndexItemType = -1;
		for (auto& Item : LocalInventoryComponent->GetItems())
		{
			FInventoryItemInfo* ItemData = GetItemData(Item.Value.ID);
			if (ItemData)
			{
				bool bIsCurrentTabItem = false;
				
				if (Item.Key != -1)
				{
					switch (ItemType)
					{
					case EItemType::IT_Consumable:
						bIsCurrentTabItem = (ItemData->Type == EItemType::IT_Consumable);
						break;
					case EItemType::IT_Miscellaneous:
						bIsCurrentTabItem = (ItemData->Type == EItemType::IT_Miscellaneous);
						break;
					case EItemType::IT_Equipment:
						bIsCurrentTabItem = (ItemData->Type == EItemType::IT_Equipment);
						break;
					case EItemType::IT_Food:
						bIsCurrentTabItem = (ItemData->Type == EItemType::IT_Food);
						break;
					case EItemType::IT_All:
						bIsCurrentTabItem = true;
						break;
					default:
						bIsCurrentTabItem = false;
						break;
					}
				}

				if (bIsCurrentTabItem && ItemType != EItemType::IT_All)
				{
					++CountIndexItemType;

					LocalInventoryComponent->SetItemOfSameType(CountIndexItemType, *LocalInventoryComponent->GetItem(Item.Key));
				}
				if (bIsCurrentTabItem && ItemType == EItemType::IT_All)
				{
					ItemData->Icon.LoadSynchronous();
					InventoryWidget->AddItem(Item.Value, *ItemData, Item.Key);
				}
			}
		}
		if (ItemType != EItemType::IT_All && LocalInventoryComponent->GetItemsOfSameTypeNum() != 0)
		{
			for (auto& ItemOfSameType : LocalInventoryComponent->GetItemsOfSameType())
			{
				FInventoryItemInfo* ItemDataOfSameType = GetItemData(ItemOfSameType.Value.ID);
				ItemDataOfSameType->Icon.LoadSynchronous();
				InventoryWidget->AddItem(ItemOfSameType.Value, *ItemDataOfSameType, ItemOfSameType.Key);
			}
		}
	}
}

void UHASInventoryManagerComponent::InitEquip(UHASInventoryComponent* InInventoryComponent)
{
	if (InInventoryComponent && EquipWidgetClass)
	{
		EquipWidget = CreateWidget<UHASInventoryWidget>(GetWorld(), EquipWidgetClass);
		EquipWidget->ParentInventory = InInventoryComponent;
		EquipWidget->OnItemDrop.AddUObject(this, &UHASInventoryManagerComponent::OnItemDropped);
		EquipWidget->AddToViewport();
	}
}

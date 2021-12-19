// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/HASInventoryManagerComponent.h"
#include "UI/Inventory/HASInventoryComponent.h"
#include "UI/Inventory/HASInventoryCellWidget.h"
#include "UI/Inventory/HASInventoryWidget.h"

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

		InventoryWidget->Init(FMath::Max(LocalInventoryComponent->GetItemsNum(), MinInventorySize));

		InventoryWidget->OnItemDrop.AddUObject(this, &UHASInventoryManagerComponent::OnItemDropped);

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

void UHASInventoryManagerComponent::OnItemDropped(UHASInventoryCellWidget* DraggedFrom, UHASInventoryCellWidget* DroppedTo)
{
	FInventorySlotInfo FromItem = DraggedFrom->GetItem();
	FInventorySlotInfo ToItem = DroppedTo->GetItem();
	
	DroppedTo->Clear();
	DraggedFrom->Clear();

	DroppedTo->AddItem(FromItem, *GetItemData(FromItem.ID));
	if (!ToItem.ID.IsNone())
	{
		DraggedFrom->AddItem(ToItem, *GetItemData(ToItem.ID));
	}
	ChangeKeyItem(FromItem, DraggedFrom->IndexInInventory, ToItem, DroppedTo->IndexInInventory);
}

void UHASInventoryManagerComponent::ChangeKeyItem(const FInventorySlotInfo& FromItemDropped, const int32 FromIndexDropped, const FInventorySlotInfo& ToItemDropped, const int32 ToIndexDropped)
{
	LocalInventoryComponent->ChangeKeyItem(FromItemDropped, FromIndexDropped, ToItemDropped, ToIndexDropped);
}

void UHASInventoryManagerComponent::OnUpdateCells(EItemType ItemType)
{
	SwitchInventoryWidgetTabs(ItemType);
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
					CountIndexItemType++;

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
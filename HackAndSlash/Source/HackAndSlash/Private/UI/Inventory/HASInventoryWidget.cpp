// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/HASInventoryWidget.h"
#include "UI/Inventory/HASInventoryCellWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UHASInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AllItemsButton)
	{
		AllItemsButton->OnClicked.AddDynamic(this, &UHASInventoryWidget::OnAllItemsClicked);
	}

	if (MiscellaneousButton)
	{
		MiscellaneousButton->OnClicked.AddDynamic(this, &UHASInventoryWidget::OnMiscellaneousClicked);
	}

	if (FoodButton)
	{
		FoodButton->OnClicked.AddDynamic(this, &UHASInventoryWidget::OnFoodClicked);
	}

	if (EquipmentButton)
	{
		EquipmentButton->OnClicked.AddDynamic(this, &UHASInventoryWidget::OnEquipmentClicked);
	}

	if (ConsumableButton)
	{
		ConsumableButton->OnClicked.AddDynamic(this, &UHASInventoryWidget::OnConsumableClicked);
	}

	for (auto* Cell : CellWidgets)
	{
		InitCell(Cell);
	}
}

void UHASInventoryWidget::Init(int32 ItemsCount)
{
	if (CellsPanel)
	{
		CellsPanel->ClearChildren();
		for (int32 i = 0; i < ItemsCount; i++)
		{
			if (UHASInventoryCellWidget* Cell = CreateCell())
			{
				Cell->IndexInInventory = i;
				CellsPanel->AddChildToUniformGrid(Cell, i / ItemsInRow, i % ItemsInRow);
			}
		}
	}
}

bool UHASInventoryWidget::AddItem(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo, int32 SlotIndex)
{
	if (ItemInfo.Type == EItemType::IT_Currency)
	{
		if (GoldCell)
		{
			return GoldCell->AddItem(SlotInfo, ItemInfo);
		}
	}

	if (CellsPanel)
	{
		UHASInventoryCellWidget* Found = nullptr;
		UHASInventoryCellWidget** FoundPtr = CellWidgets.FindByPredicate([SlotIndex](UHASInventoryCellWidget* CellWidget)
		{
				return CellWidget && CellWidget->IndexInInventory == SlotIndex;
		});

		if (FoundPtr)
		{
			Found = *FoundPtr;
		}
		else
		{
			for (UHASInventoryCellWidget* CellWidget : CellWidgets)
			{
				if (!CellWidget->HasItem())
				{
					Found = CellWidget;
					break;
				}
			}
		}
		if (Found)
		{
			return Found->AddItem(SlotInfo, ItemInfo);
		}
	}
	return false;
}

UHASInventoryCellWidget* UHASInventoryWidget::CreateCell()
{
	if (CellWidgetClass)
	{
		UHASInventoryCellWidget* CellWidget = CreateWidget<UHASInventoryCellWidget>(this, CellWidgetClass);
		CellWidgets.Add(CellWidget);

		InitCell(CellWidget);

		return CellWidget;
	}
	return nullptr;
}

void UHASInventoryWidget::InitCell(UHASInventoryCellWidget* NewCell)
{
	if (NewCell)
	{
		NewCell->OnItemDrop.AddUObject(this, &UHASInventoryWidget::OnItemDropped);
		NewCell->OnItemClick.AddUObject(this, &UHASInventoryWidget::OnItemClicked);
		NewCell->ParentInventoryWidget = this;
	}
}

void UHASInventoryWidget::ClearItems()
{
	for (auto CellWidget : CellWidgets)
	{
		CellWidget->Clear();
	}
}

void UHASInventoryWidget::OnItemDropped(UHASInventoryCellWidget* DraggedFrom, UHASInventoryCellWidget* DroppedTo)
{
	if (OnItemDrop.IsBound())
	{
		OnItemDrop.Broadcast(DraggedFrom, DroppedTo);
	}
}

void UHASInventoryWidget::OnItemClicked(UHASInventoryCellWidget* OnItemClickCell)
{
	if (OnItemClick.IsBound())
	{
		OnItemClick.Broadcast(OnItemClickCell);
	}
}

void UHASInventoryWidget::OnAllItemsClicked()
{
	CurrentTabType = EItemType::IT_All;
	OnUpdateCells.Broadcast(CurrentTabType);
}

void UHASInventoryWidget::OnMiscellaneousClicked()
{
	CurrentTabType = EItemType::IT_Miscellaneous;
	OnUpdateCells.Broadcast(CurrentTabType);
}

void UHASInventoryWidget::OnFoodClicked()
{
	CurrentTabType = EItemType::IT_Food;
	OnUpdateCells.Broadcast(CurrentTabType);
}

void UHASInventoryWidget::OnEquipmentClicked()
{
	CurrentTabType = EItemType::IT_Equipment;
	OnUpdateCells.Broadcast(CurrentTabType);
}

void UHASInventoryWidget::OnConsumableClicked()
{
	CurrentTabType = EItemType::IT_Consumable;
	OnUpdateCells.Broadcast(CurrentTabType);
}

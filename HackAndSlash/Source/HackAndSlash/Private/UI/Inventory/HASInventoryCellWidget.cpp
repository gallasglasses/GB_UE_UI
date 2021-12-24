// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/HASInventoryCellWidget.h"
#include "UI/Inventory/HASInventoryDragDropOperation.h"
#include "UI/Inventory/HASInventoryComponent.h"
#include "UI/Inventory/HASInventoryWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

UHASInventoryComponent* UHASInventoryCellWidget::GetParentInventoryWidget() const
{
	return ParentInventoryWidget ? ParentInventoryWidget->ParentInventory : nullptr;
}

bool UHASInventoryCellWidget::AddItem(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo)
{
	if (bHasItem)
	{
		return false;
	}

	if (ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ItemVisualTexture = ItemInfo.Icon.LoadSynchronous();
		ItemImage->SetBrushFromTexture(ItemVisualTexture);
	}

	if (ItemCountText)
	{
		ItemCountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ItemCountVisualText = SlotInfo.Count;
		ItemCountText->SetText(FText::FromString(FString::FromInt(ItemCountVisualText)));
	}

	bHasItem = true;
	Item = SlotInfo;

	return true;
}

bool UHASInventoryCellWidget::HasItem() const
{
	return bHasItem;
}

void UHASInventoryCellWidget::Clear()
{
	if (!bHasItem)
	{
		return;
	}

	if (ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::Collapsed);
		ItemImage->SetBrush(FSlateBrush());
		ItemVisualTexture = nullptr;
	}

	if (ItemCountText)
	{
		ItemCountText->SetVisibility(ESlateVisibility::Collapsed);
		ItemCountText->SetText(FText::FromString("0"));
	}

	bHasItem = false;
	Item = FInventorySlotInfo();
}

const FInventorySlotInfo& UHASInventoryCellWidget::GetItem() const
{
	return Item;
}

FReply UHASInventoryCellWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bIsDraggable && bHasItem &&	InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}

	if (bIsDraggable && bHasItem && InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		OnItemClick.Broadcast(this);
		//return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::RightMouseButton).NativeReply;
	}
	return FReply::Handled();
}

void UHASInventoryCellWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UHASInventoryDragDropOperation::StaticClass());
	
	if (OutOperation)
	{
		UHASInventoryDragDropOperation* InventoryDragDropOperation = Cast<UHASInventoryDragDropOperation>(OutOperation);
		UHASInventoryCellWidget* DragVisualWidget = CreateWidget<UHASInventoryCellWidget>(GetWorld(), DragVisualWidgetClass);

		if (DragVisualWidget && DragVisualWidget->ItemImage)
		{
			DragVisualWidget->ItemImage->SetBrushFromTexture(ItemVisualTexture);
			DragVisualWidget->ItemImage->SetVisibility(ESlateVisibility::Visible);
			DragVisualWidget->ItemCountText->SetText(FText::FromString(FString::FromInt(ItemCountVisualText)));
			DragVisualWidget->ItemCountText->SetVisibility(ESlateVisibility::Visible);
		}

		if (InventoryDragDropOperation)
		{
			InventoryDragDropOperation->DragVisualWidget = this;
			InventoryDragDropOperation->DefaultDragVisual = DragVisualWidget;
			InventoryDragDropOperation->Pivot = EDragPivot::MouseDown;
		}
	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}

}

bool UHASInventoryCellWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UHASInventoryDragDropOperation* InventoryDragDropOperation = Cast<UHASInventoryDragDropOperation>(InOperation);
	if (InventoryDragDropOperation && (InventoryDragDropOperation->DefaultDragVisual != this || InventoryDragDropOperation->DragVisualWidget != this))
	{
		if (OnItemDrop.IsBound())
		{
			OnItemDrop.Broadcast(InventoryDragDropOperation->DragVisualWidget, this);
			return true;
		}
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

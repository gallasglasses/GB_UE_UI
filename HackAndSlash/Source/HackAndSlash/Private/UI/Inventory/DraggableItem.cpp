// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/DraggableItem.h"
#include "UI/Inventory/ItemDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HASPlayerController.h"

void UDraggableItem::NativePreConstruct()
{
	if (TextDraggableItem)
	{
		TextDraggableItem->SetText(FText::FromString(NameDraggableItem));
	}
}

FReply UDraggableItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{		
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}

	return FReply::Handled();
}

void UDraggableItem::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& Operation)
{
	Operation = UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDragDropOperation::StaticClass());
	UItemDragDropOperation* ItemOperation = Cast<UItemDragDropOperation>(Operation);

	if (ItemOperation)
	{
		ItemOperation->DefaultDragVisual = this;
		
		SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.7f));
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		ItemOperation->OnDragCancelled.AddDynamic(this, &ThisClass::RestoreVisuals);
	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, Operation);
	}
}

bool UDraggableItem::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UVerticalBox* VerticalBox = Cast<UVerticalBox>(GetParent());
	UItemDragDropOperation* ItemOperation = Cast<UItemDragDropOperation>(InOperation);

	if (VerticalBox && ItemOperation && ItemOperation->DefaultDragVisual && this != ItemOperation->DefaultDragVisual)
	{
		const int32 OverIndex = VerticalBox->GetChildIndex(ItemOperation->DefaultDragVisual);
		UWidget* DroppedWidget = ItemOperation->DefaultDragVisual;

		if (OverIndex >= 0)
		{
			//USlateBlueprintLibrary::LocalToViewport(InGeometry);
			//!!! DEPRECATED !!! -> InGeometry.Position, but what i can to use?
			const int32 DroppedToIndex = InGeometry.Position.Y / InGeometry.GetLocalSize().Y;

			/*float delta = InGeometry.GetAbsolutePosition().Y - InGeometry.Position.Y;
			float MouseOnWidget = InDragDropEvent.GetLastScreenSpacePosition().Y - delta;
			const int32 DroppedToIndex = MouseOnWidget/ InGeometry.GetLocalSize().Y;*/
			
			VerticalBox->RemoveChildAt(OverIndex);

			auto Children = VerticalBox->GetAllChildren();
			
			VerticalBox->ClearChildren();
			Children.Insert(DroppedWidget, DroppedToIndex);
			for (int32 i = 0; i < Children.Num(); i++)
			{
				
				VerticalBox->AddChildToVerticalBox(Children[i])->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);

 				/*if (Children[i] == this)
 				{
 					VerticalBox->AddChildToVerticalBox(ItemOperation->DefaultDragVisual)->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
 				}*/
			}
			return true;
		}
	}

	return Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
}

bool UDraggableItem::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (InOperation && InOperation->DefaultDragVisual)
	{
		RestoreVisuals(InOperation);
		return true;
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UDraggableItem::RestoreVisuals(UDragDropOperation* Operation)
{
	UDraggableItem* Item = Cast<UDraggableItem>(Operation->DefaultDragVisual);
	if (Item)
	{
		SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		SetVisibility(ESlateVisibility::Visible);
	}
}

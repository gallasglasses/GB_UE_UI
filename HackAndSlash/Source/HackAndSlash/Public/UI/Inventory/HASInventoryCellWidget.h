// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Inventory/HASInventoryData.h"
#include "HASInventoryCellWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class HACKANDSLASH_API UHASInventoryCellWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ItemCountText;

	bool bHasItem;

	UPROPERTY()
	FInventorySlotInfo Item;

public:

	FOnItemDrop OnItemDrop;

	bool AddItem(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo);
	bool HasItem() const;

	void Clear();

	const FInventorySlotInfo& GetItem() const;

	int32 IndexInInventory = INDEX_NONE;

protected:
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry,const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UPROPERTY(EditAnywhere)
	bool bIsDraggable = true;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHASInventoryCellWidget> DragVisualWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* ItemVisualTexture = nullptr;

	int32 ItemCountVisualText;

};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HASInventoryData.h"
#include "HASInventoryWidget.generated.h"

class UHASInventoryCellWidget;
class UHASInventoryComponent;
class UUniformGridPanel;
class UButton;
class UTextBlock;
class UImage;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateCells, EItemType);

UCLASS()
class INVENTORYSYSTEM_API UHASInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	FOnUpdateCells OnUpdateCells;
	FOnItemDrop OnItemDrop;
	FOnItemClick OnItemClick;

	UPROPERTY()
		UHASInventoryComponent* ParentInventory;

	virtual void NativeConstruct() override;

	void Init(int32 ItemsCount);
	void ClearItems();

	bool AddItem(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo, int32 SlotIndex);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UUniformGridPanel* CellsPanel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UHASInventoryCellWidget* GoldCell;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UHASInventoryCellWidget* RightHandCellWeaponry;
						
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UHASInventoryCellWidget* LeftHandCellWeaponry;
						
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UHASInventoryCellWidget* AddRightHandCellWeaponry;
						
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UHASInventoryCellWidget* AddLeftHandCellWeaponry;
						
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UHASInventoryCellWidget* HeadCellEquip;
						
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UHASInventoryCellWidget* HandsCellEquip;
						
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UHASInventoryCellWidget* BodyCellEquip;
						
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UHASInventoryCellWidget* LegsCellEquip;
						
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UHASInventoryCellWidget* FeetCellEquip;

	UPROPERTY(meta = (BindWidgetOptional))
		UButton* AllItemsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UImage* AllItemsImage;

	UPROPERTY(meta = (BindWidgetOptional))
		UButton* MiscellaneousButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UImage* MiscellaneousImage;

	UPROPERTY(meta = (BindWidgetOptional))
		UButton* FoodButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UImage* FoodImage;

	UPROPERTY(meta = (BindWidgetOptional))
		UButton* EquipmentButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UImage* EquipmentImage;

	UPROPERTY(meta = (BindWidgetOptional))
		UButton* ConsumableButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UImage* ConsumableImage;

	UPROPERTY(EditDefaultsOnly)
		int32 ItemsInRow = 5;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UHASInventoryCellWidget> CellWidgetClass;

	UPROPERTY(BlueprintReadWrite)
		TArray<UHASInventoryCellWidget*> CellWidgets;

	UPROPERTY(BlueprintReadWrite)
		TArray<UHASInventoryCellWidget*> EquipCellWidgets;

	UHASInventoryCellWidget* CreateCell();

	void InitCell(UHASInventoryCellWidget* NewCell);

	void OnItemDropped(UHASInventoryCellWidget* DraggedFrom, UHASInventoryCellWidget* DroppedTo);
	void OnItemClicked(UHASInventoryCellWidget* OnItemClickCell);

	EItemType CurrentTabType = EItemType::IT_All;
private:
	UFUNCTION()
		void OnAllItemsClicked();

	UFUNCTION()
		void OnMiscellaneousClicked();

	UFUNCTION()
		void OnFoodClicked();

	UFUNCTION()
		void OnEquipmentClicked();

	UFUNCTION()
		void OnConsumableClicked();
};
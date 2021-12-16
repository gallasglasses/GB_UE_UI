// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Inventory/HASInventoryData.h"
#include "HASInventoryWidget.generated.h"

class UHASInventoryCellWidget;
class UUniformGridPanel;
class UButton;
class UTextBlock;
class UImage;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateCells, EItemType);

UCLASS()
class HACKANDSLASH_API UHASInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	FOnUpdateCells OnUpdateCells;
	FOnItemDrop OnItemDrop;

	virtual void NativeConstruct() override;

	void Init(int32 ItemsCount);
	void ClearItems();

	bool AddItem(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo, int32 SlotIndex);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UUniformGridPanel* CellsPanel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UHASInventoryCellWidget* GoldCell;

	UPROPERTY(meta = (BindWidget))
		UButton* AllItemsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* AllItemsImage;

	UPROPERTY(meta = (BindWidget))
		UButton* MiscellaneousButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* MiscellaneousImage;

	UPROPERTY(meta = (BindWidget))
		UButton* FoodButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* FoodImage;

	UPROPERTY(meta = (BindWidget))
		UButton* EquipmentButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* EquipmentImage;

	UPROPERTY(meta = (BindWidget))
		UButton* ConsumableButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* ConsumableImage;

	UPROPERTY(EditDefaultsOnly)
	int32 ItemsInRow = 5;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHASInventoryCellWidget> CellWidgetClass;

	UPROPERTY()
	TArray<UHASInventoryCellWidget*> CellWidgets; 

	UHASInventoryCellWidget* CreateCell();

	void OnItemDropped(UHASInventoryCellWidget* DraggedFrom, UHASInventoryCellWidget* DroppedTo);

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
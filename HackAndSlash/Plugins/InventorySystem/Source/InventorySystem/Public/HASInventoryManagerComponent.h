// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HASInventoryData.h"
#include "HASInventoryManagerComponent.generated.h"

class UHASInventoryComponent;
class UDataTable;
class UHASInventoryWidget;
class UHASInventoryCellWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemUse, FName /*ItemId*/);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UHASInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UHASInventoryManagerComponent();

	FOnItemUse OnItemUse;

	void Init(UHASInventoryComponent* InInventoryComponent);

	void InitEquip(UHASInventoryComponent* InInventoryComponent);

	void SwitchInventoryWidgetTabs(EItemType ItemType);

	void RemoveInventory();

	void RemoveEquip();

	FInventoryItemInfo* GetItemData(const FName& InID) const;

protected:

	UPROPERTY()
		UHASInventoryComponent* LocalInventoryComponent;

	UPROPERTY(EditAnywhere)
		UDataTable* ItemsData;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UHASInventoryWidget> InventoryWidgetClass;

	UPROPERTY()
		UHASInventoryWidget* InventoryWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UHASInventoryWidget> EquipWidgetClass;

	UPROPERTY()
		UHASInventoryWidget* EquipWidget;

	UPROPERTY(EditAnywhere)
		int32 MinInventorySize = 20;

	void OnItemDropped(UHASInventoryCellWidget* DraggedFrom, UHASInventoryCellWidget* DroppedTo);
	void OnUpdateCells(EItemType ItemType);
	void OnItemClicked(UHASInventoryCellWidget* OnItemClickCell);
	void ChangeKeyItem(const FInventorySlotInfo& FromItemDropped, const int32 FromIndexDropped, const FInventorySlotInfo& ToItemDropped, const int32 ToIndexDropped);
};
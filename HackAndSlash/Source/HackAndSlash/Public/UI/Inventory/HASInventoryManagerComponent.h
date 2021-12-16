// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UI/Inventory/HASInventoryData.h"
#include "HASInventoryManagerComponent.generated.h"

class UHASInventoryComponent;
class UDataTable;
class UHASInventoryWidget;
class UHASInventoryCellWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKANDSLASH_API UHASInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UHASInventoryManagerComponent();

	void Init(UHASInventoryComponent* InInventoryComponent);
	void SwitchInventoryWidgetTabs(EItemType ItemType);

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
	int32 MinInventorySize = 20;

	void OnItemDropped(UHASInventoryCellWidget* DraggedFrom, UHASInventoryCellWidget* DroppedTo);
	void OnUpdateCells(EItemType ItemType);
};

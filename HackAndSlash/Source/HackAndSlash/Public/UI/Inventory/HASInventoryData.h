// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
//#include "UI/Inventory/HASInventoryCellWidget.h"
#include "HASInventoryData.generated.h"

UENUM()
enum class EItemType : uint8
{
	IT_All,
	IT_Miscellaneous,
	IT_Currency,
	IT_Equipment,
	IT_Consumable,
	IT_Food
};

UENUM()
enum class EItemRarity : uint8
{
	IR_Common,
	IR_Rare,
	IR_Epic,
	IR_Legendary
};

class UHASInventoryCellWidget;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemDrop, UHASInventoryCellWidget* /*DraggedFrom*/, UHASInventoryCellWidget* /*DroppedTo*/);

USTRUCT(BlueprintType)
struct FInventoryItemInfo : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = "General")
		FName ID = NAME_None;

	UPROPERTY(EditAnywhere, Category = "General")
		FText Name;

	UPROPERTY(EditAnywhere, Category = "General")
		FText Description;

	UPROPERTY(EditAnywhere, Category = "Visual")
		TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, Category = "Visual")
		TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, Category = "Type")
		EItemType Type;

	UPROPERTY(EditAnywhere, Category = "Type")
		EItemRarity Rarity;

	UPROPERTY(EditAnywhere, Category = "Stats")
		int32 Damage;

	UPROPERTY(EditAnywhere, Category = "Stats")
		int32 Armor;

	UPROPERTY(EditAnywhere, Category = "Stats")
		int32 Intelligence;
};

USTRUCT(BlueprintType)
struct FInventorySlotInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName ID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Count = INDEX_NONE;
};
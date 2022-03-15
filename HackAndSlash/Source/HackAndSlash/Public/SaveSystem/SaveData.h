#pragma once

#include "CoreMinimal.h"
#include "HASInventoryData.h"
#include "SaveData.generated.h"

USTRUCT(BlueprintType)
struct FCharacterSaveData
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
		FName ActorName;

	UPROPERTY()
		FTransform Transform;

	UPROPERTY()
		float Health;

	UPROPERTY()
		TMap<int32, FInventorySlotInfo> InventoryItems;

	UPROPERTY()
		TMap<int32, FInventorySlotInfo> EquipItems;

};

USTRUCT(BlueprintType)
struct FLootSaveData
{
	GENERATED_BODY()

public:

	UPROPERTY()
		FName ActorName;

	UPROPERTY()
		TMap<int32, FInventorySlotInfo> InventoryItems;
};
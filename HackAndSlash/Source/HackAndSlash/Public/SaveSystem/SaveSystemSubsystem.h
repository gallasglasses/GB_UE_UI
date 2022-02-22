// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SaveData.h"
#include "Pickups/HASLootBox.h"
#include "SaveSystemSubsystem.generated.h"

class AHASLootBox;
/**
 * 
 */
UCLASS()
class HACKANDSLASH_API USaveSystemSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		TMap<FName, AHASLootBox*> SavedLoots;

public:

	UFUNCTION(BlueprintCallable)
	void SetLoot(FName Name, AHASLootBox* Loots) { SavedLoots.Add(Name, Loots); }
	
	UFUNCTION(BlueprintCallable)
	TMap<FName, AHASLootBox*> GetLoots() const { return SavedLoots; }
};

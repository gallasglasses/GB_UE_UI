// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveData.h"
#include "SaveSystemSubsystem.h"
#include "HASSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite)
	float TestFloat;

	UPROPERTY(BlueprintReadWrite)
	FCharacterSaveData CharacterSaveData;

	UPROPERTY(BlueprintReadWrite)
	TMap<FName,FLootSaveData> LootSaveData;

	UPROPERTY(BlueprintReadWrite)
	USaveSystemSubsystem* SaveSystemSubsystem;
};

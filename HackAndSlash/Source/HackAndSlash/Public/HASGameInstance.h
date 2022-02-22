// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HASGameInstance.generated.h"

class USaveManager;

UCLASS()
class HACKANDSLASH_API UHASGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	virtual void Init() override;

	UFUNCTION(BlueprintPure, meta= (WorldContext = WorldContextObject))
	static USaveManager* GetSaveManager(UObject* WorldContextObject);

protected:

	UPROPERTY()
	USaveManager* SaveManager;

};

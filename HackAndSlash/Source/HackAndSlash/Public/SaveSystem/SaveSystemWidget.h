// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveSystemWidget.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API USaveSystemWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
	void SaveLootsData();

	UFUNCTION(BlueprintCallable)
	void LoadLootsData();
};

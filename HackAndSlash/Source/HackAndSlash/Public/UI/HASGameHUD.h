// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HASGameHUD.generated.h"

UCLASS()
class HACKANDSLASH_API AHASGameHUD : public AHUD
{
	GENERATED_BODY()

  protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

  	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
  	TSubclassOf<UUserWidget> GameOverWidgetClass;
  
  	virtual void BeginPlay() override;
};
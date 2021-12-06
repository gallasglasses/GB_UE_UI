// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HASGameHUD.generated.h"

class UHASMiniMapWidget;

UCLASS()
class HACKANDSLASH_API AHASGameHUD : public AHUD
{
	GENERATED_BODY()

 protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

  	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
  	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MiniMapWidget;
  
  	virtual void BeginPlay() override;

private:
	UHASMiniMapWidget* MiniMapHUDWidget;

public:
	void SetPlayerHUDPosition(FVector2D PlayerHUDPosition);
	//FVector2D PlayerPosition;
};
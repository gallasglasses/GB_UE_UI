// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HASGameHUD.generated.h"

class UHASMiniMapWidget;
class UUserWidget;

UENUM()
enum class EWidgetID : uint8 
{
	WID_MainMenu,
	WID_EscapeMenu,
	WID_PlayerUI,
	WID_GameOver,
	WID_MiniMap,
	WID_Inventory
};

UCLASS()
class HACKANDSLASH_API AHASGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UUserWidget* CreateWidgetByClass(const TSubclassOf<UUserWidget> MenuWidgetClass, const int32 ZOrder = 0);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TMap<EWidgetID, TSubclassOf<UUserWidget>> MenuWidgetClasses;

	virtual void BeginPlay() override;

	UPROPERTY()
		UUserWidget* CurrentWidget;

public:
	UFUNCTION(BlueprintCallable)
		UUserWidget* GetCurrentWidget() const;

	UFUNCTION(BlueprintCallable)
		UUserWidget* ShowWidget(const EWidgetID WidgetID, const int32 ZOrder = 0);

	UFUNCTION(BlueprintCallable)
		void HideWidget();

private:
	UHASMiniMapWidget* MiniMapHUDWidget;

public:
	void SetPlayerHUDPosition(FVector2D PlayerHUDPosition);

//protected:
//
//	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
//		TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
//
//	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
//		TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> MiniMapWidget;
};
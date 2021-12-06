// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HASGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/HASMiniMapWidget.h"

DEFINE_LOG_CATEGORY_STATIC(GameHUDLog, All, All);

void AHASGameHUD::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}

	MiniMapHUDWidget = CreateWidget<UHASMiniMapWidget>(GetWorld(), MiniMapWidget);
	if (MiniMapHUDWidget)
	{
		MiniMapHUDWidget->AddToViewport();
	}
}

void AHASGameHUD::SetPlayerHUDPosition(FVector2D PlayerHUDPosition)
{
	if (UHASMiniMapWidget* MiniMap = Cast<UHASMiniMapWidget>(MiniMapHUDWidget))
	{
		UE_LOG(GameHUDLog, Display, TEXT("!!!GameHUDLog X %f, Y %f "), PlayerHUDPosition.X, PlayerHUDPosition.Y);

		MiniMap->SetPlayerWidgetPosition(PlayerHUDPosition);
	}
}
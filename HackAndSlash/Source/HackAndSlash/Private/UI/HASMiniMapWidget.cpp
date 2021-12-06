// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HASMiniMapWidget.h"
#include "UI/MiniMap.h"
#include "Components/CanvasPanelSlot.h"

void UHASMiniMapWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (WMinimap)
	{
		Cast<UCanvasPanelSlot>(WMinimap->Slot)->SetSize(FVector2D (200.f,200.f));
	}
}

void UHASMiniMapWidget::SetPlayerWidgetPosition(FVector2D PlayerWidgetPosition)
{
	WMinimap->SetPlayerMapPosition(PlayerWidgetPosition);
}
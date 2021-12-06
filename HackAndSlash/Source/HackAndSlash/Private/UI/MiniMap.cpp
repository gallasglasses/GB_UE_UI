// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MiniMap.h"
#include "UI/SHASSlateMiniMapWidget.h"
#include "UI/MiniMapCoreStyle.h"

void UMiniMap::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MiniMap.Reset();
}

TSharedRef<SWidget> UMiniMap::RebuildWidget()
{
	MiniMap = SNew(SHASSlateMiniMapWidget);
	return MiniMap.ToSharedRef();
}

void UMiniMap::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (MiniMap.IsValid())
	{
		MiniMap->SetBrushes(FMiniMapCoreStyle::Get().GetBrush("SPlayerPointImage"), FMiniMapCoreStyle::Get().GetBrush("SMiniMapImage"));	
	}
}

void UMiniMap::SetPlayerMapPosition(FVector2D PlayerMapPosition)
{
	if (MiniMap.IsValid())
	{
		MiniMap->SetPlayerPosition(PlayerMapPosition);
	}
}
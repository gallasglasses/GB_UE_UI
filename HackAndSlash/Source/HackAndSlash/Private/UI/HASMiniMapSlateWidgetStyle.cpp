// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HASMiniMapSlateWidgetStyle.h"

FHASMiniMapSlateStyle::FHASMiniMapSlateStyle()
{
}

FHASMiniMapSlateStyle::~FHASMiniMapSlateStyle()
{
}

const FName FHASMiniMapSlateStyle::TypeName(TEXT("FHASMiniMapSlateStyle"));

const FHASMiniMapSlateStyle& FHASMiniMapSlateStyle::GetDefault()
{
	static FHASMiniMapSlateStyle Default;
	return Default;
}

void FHASMiniMapSlateStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class FInvalidatableBrushAttribute;

class HACKANDSLASH_API SHASSlateMiniMapWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SHASSlateMiniMapWidget)
	: _MiniMapBorder(FCoreStyle::Get().GetDefaultBrush()),
		_MiniMap(FCoreStyle::Get().GetDefaultBrush()),
		_PlayerPoint(FCoreStyle::Get().GetDefaultBrush())
	{
	}

	SLATE_ATTRIBUTE(const FSlateBrush*, MiniMapBorder)
	SLATE_ATTRIBUTE(const FSlateBrush*, MiniMap)
	SLATE_ATTRIBUTE(const FSlateBrush*, PlayerPoint)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

protected:

	FInvalidatableBrushAttribute MiniMapBorder;
	FInvalidatableBrushAttribute MiniMap;
	FInvalidatableBrushAttribute PlayerPoint;

	FVector2D PlayerPositionOnMap;

public:
	virtual int32 OnPaint(
		const FPaintArgs& Args,
		const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect,
		FSlateWindowElementList& OutDrawElements,
		int32 LayerId,
		const FWidgetStyle& InWidgetStyle,
		bool bParentEnabled
	) const override;

	void SetPlayerPosition(FVector2D PlayerPosition);
	void SetBrushes(TAttribute<const FSlateBrush*> BrushPoint, TAttribute<const FSlateBrush*> BrushMap);
};
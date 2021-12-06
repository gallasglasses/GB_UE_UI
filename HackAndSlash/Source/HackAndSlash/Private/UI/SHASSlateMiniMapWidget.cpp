// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SHASSlateMiniMapWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SHASSlateMiniMapWidget::Construct(const FArguments& InArgs)
{
	MiniMapBorder = InArgs._MiniMapBorder;
	MiniMap = InArgs._MiniMap;
	PlayerPoint = InArgs._PlayerPoint;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

int32 SHASSlateMiniMapWidget::OnPaint(
	const FPaintArgs& Args,
	const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements,
	int32 LayerId,
	const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled
) const
{
	const FSlateBrush* MiniMapImage = MiniMap.GetImage().Get();

	if (MiniMapImage)
	{
		const ESlateDrawEffect DrawEffects = this->ShouldBeEnabled(bParentEnabled) ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			MiniMapImage,
			DrawEffects
		);
	}

	++LayerId;

	const FSlateBrush* PlayerPointImage = PlayerPoint.GetImage().Get();
	if (PlayerPointImage)
	{
		const ESlateDrawEffect DrawEffects = this->ShouldBeEnabled(bParentEnabled) ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;
		
		const FVector2D PlayerPointSize(10.f);
		const FVector2D PlayerPointOnCenter(PlayerPointSize * 0.5f);
		const FVector2D PlayerPointRelativePosition(FVector2D(200.f, 200.f) * 0.5f - PlayerPointOnCenter + PlayerPositionOnMap);
		const FSlateLayoutTransform PlayerPointTransform(1.0f, PlayerPointRelativePosition);
		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(PlayerPointSize, PlayerPointTransform),
			PlayerPointImage,
			DrawEffects
		);
	}

	/*++LayerId;
	
	const FSlateBrush* MiniMapBorderImage = MiniMapBorder.GetImage().Get();
	if (MiniMapBorderImage)
	{
		
		const ESlateDrawEffect DrawEffects = this->ShouldBeEnabled(bParentEnabled) ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;
		
		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			MiniMapBorderImage,
			DrawEffects
		);
	}*/

	return LayerId;
}

void SHASSlateMiniMapWidget::SetBrushes(TAttribute<const FSlateBrush*> BrushPoint, TAttribute<const FSlateBrush*> BrushMap)
{
	//MiniMapBorder.SetImage(*this, BrushBorder);
	PlayerPoint.SetImage(*this, BrushPoint);
	MiniMap.SetImage(*this, BrushMap);
}

void SHASSlateMiniMapWidget::SetPlayerPosition(FVector2D PlayerPosition)
{
	float ScaleMap = 200.f / 12000.f;
	FVector2D PlayerPositionRelativeMap(-PlayerPosition.X, -PlayerPosition.Y);

	PlayerPositionOnMap = PlayerPositionRelativeMap * ScaleMap;
}
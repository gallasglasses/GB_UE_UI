// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "MiniMap.generated.h"

class SHASSlateMiniMapWidget;

UCLASS()
class HACKANDSLASH_API UMiniMap : public UWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Brushes")
		FSlateBrush MiniMapBorder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Brushes")
		FSlateBrush MiniMapWorld;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Brushes")
		FSlateBrush MiniMapPointer;

	void SetPlayerMapPosition(FVector2D PlayerMapPosition);

protected:

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void SynchronizeProperties() override;
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SHASSlateMiniMapWidget> MiniMap;
};

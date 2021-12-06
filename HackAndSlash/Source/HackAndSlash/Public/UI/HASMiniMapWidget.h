// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HASMiniMapWidget.generated.h"

class UMiniMap;

UCLASS()
class HACKANDSLASH_API UHASMiniMapWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UMiniMap* WMinimap;

	virtual void NativePreConstruct() override;

public:
	void SetPlayerWidgetPosition(FVector2D PlayerWidgetPosition);
};

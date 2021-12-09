// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "MenuDefaultWidgetStyle.generated.h"

USTRUCT()
struct HACKANDSLASH_API FMenuDefaultStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

		FMenuDefaultStyle();
	virtual ~FMenuDefaultStyle();

	UPROPERTY(EditAnywhere, Category = Appearance)
		FButtonStyle ButtonStyle;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FTextBlockStyle TextButtonStyle;
	
	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FMenuDefaultStyle& GetDefault();
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UMenuDefaultWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
		FMenuDefaultStyle WidgetStyle;

	virtual const struct FMenuDefaultStyle* const GetStyle() const override
	{
		return static_cast< const struct FMenuDefaultStyle* >( &WidgetStyle );
	}
};

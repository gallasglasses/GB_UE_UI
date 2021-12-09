// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Menu/UI/Styles/RadioButtonsWidgetStyle.h"
#include "Widgets/SCompoundWidget.h"
#include "Styling/SlateTypes.h"

DECLARE_DELEGATE_OneParam(FOnRadioButtonChanged, int32 /*NewSelectedIndex*/)

class HACKANDSLASH_API SHASSlateRadioButton : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SHASSlateRadioButton)
	{
	
	}

	SLATE_EVENT(FOnRadioButtonChanged, OnRadioButtonChanged);
	SLATE_STYLE_ARGUMENT(FRadioButtonsStyle, Style);

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FOnRadioButtonChanged OnRadioButtonChanged;

	private:

	TSharedRef<SWidget> CreateCheckBox(int32 InIndex, FString InText);

	int32 CurrentIndex = 0;

	ECheckBoxState IsChecked(int32 InIndex) const;

	void OnCheckBoxStateChanged(ECheckBoxState NewState, int32 InIndex);

	const FCheckBoxStyle* CheckBoxStyle = nullptr;
	const FTextBlockStyle* TextStyle = nullptr;
};

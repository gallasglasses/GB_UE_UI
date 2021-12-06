// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_OneParam(FOnRadioButtonChanged, int32 /*NewSelectedIndex*/)

class HACKANDSLASH_API SHASSlateRadioButton : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SHASSlateRadioButton)
	{
	
	}

	SLATE_EVENT(FOnRadioButtonChanged, OnRadioButtonChanged);

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FOnRadioButtonChanged OnRadioButtonChanged;

	private:

	TSharedRef<SWidget> CreateCheckBox(int32 InIndex, FString InText);

	int32 CurrentIndex = 0;

	ECheckBoxState IsChecked(int32 InIndex) const;

	void OnCheckBoxStateChanged(ECheckBoxState NewState, int32 InIndex);
};

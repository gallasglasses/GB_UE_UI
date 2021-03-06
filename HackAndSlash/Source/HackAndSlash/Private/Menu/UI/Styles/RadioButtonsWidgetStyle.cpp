// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/Styles/RadioButtonsWidgetStyle.h"

FRadioButtonsStyle::FRadioButtonsStyle()
{
	CheckBoxStyle = FCoreStyle::Get().GetWidgetStyle<FCheckBoxStyle>("Checkbox");
	TextStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");
}

FRadioButtonsStyle::~FRadioButtonsStyle()
{
}

const FName FRadioButtonsStyle::TypeName(TEXT("FRadioButtonsStyle"));

const FRadioButtonsStyle& FRadioButtonsStyle::GetDefault()
{
	static FRadioButtonsStyle Default;
	return Default;
}

void FRadioButtonsStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	//FRadioButtonsStyle::GetResources(OutBrushes);

 	CheckBoxStyle.GetResources(OutBrushes);
 	TextStyle.GetResources(OutBrushes);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/Styles/MenuDefaultWidgetStyle.h"

FMenuDefaultStyle::FMenuDefaultStyle()
{
	ButtonStyle = FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button");
	TextButtonStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");
}

FMenuDefaultStyle::~FMenuDefaultStyle()
{

}

const FName FMenuDefaultStyle::TypeName(TEXT("FMenuDefaultStyle"));

const FMenuDefaultStyle& FMenuDefaultStyle::GetDefault()
{
	static FMenuDefaultStyle Default;
	return Default;
}

void FMenuDefaultStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{

}


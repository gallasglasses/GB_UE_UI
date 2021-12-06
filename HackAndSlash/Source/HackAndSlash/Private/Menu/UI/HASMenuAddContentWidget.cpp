// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/HASMenuAddContentWidget.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Components/Image.h"
#include "Components/NativeWidgetHost.h"
#include "Menu/UI/SHASSlateRadioButton.h"
//#include "UI/MiniMapCoreStyle.h"

void UHASMenuAddContentWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (RadioButtonsHost)
	{
		RadioButtonsHost->SetContent(SNew(SHASSlateRadioButton));
	}

	/*if (BorderImage)
	{
		BorderImage->SetBrush(*FMiniMapCoreStyle::Get().GetBrush("SMiniMapBorder"));
		Cast<UButtonSlot>(BorderImage->Slot)->SetPadding(FMiniMapCoreStyle::Get().GetMargin("DefaultPadding"));
	}*/
}

void UHASMenuAddContentWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RadioButtonsHost)
	{
		RadioButtonsHost->SetContent(SNew(SHASSlateRadioButton));
	}
}

UButton* UHASMenuAddContentWidget::GetBackToMenuButton()
{
	if (BackToMenuButton)
	{
		return BackToMenuButton;
	}
	return nullptr;
}
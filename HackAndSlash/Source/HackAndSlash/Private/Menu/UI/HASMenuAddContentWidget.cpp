// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/UI/RadioButtons.h"
#include "Menu/UI/HASMenuAddContentWidget.h"
#include "Menu/UI/Styles/RadioButtonsWidgetStyle.h"
#include "Menu/UI/Styles/MenuCoreStyle.h"
#include "Menu/UI/Styles/MenuDefaultWidgetStyle.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Components/Image.h"
#include "Components/NativeWidgetHost.h"
#include "Menu/UI/SHASSlateRadioButton.h"
//#include "UI/MiniMapCoreStyle.h"

void UHASMenuAddContentWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

// 	if (RadioButtonsHost)
// 	{
// 		RadioButtonsHost->SetContent(SNew(SHASSlateRadioButton));
// 	}

	SetWidgetStyle();
	SetMenuTheme(WidgetStyle);

	if (BoxRadioButtons)
	{
		BoxRadioButtons->WidgetStyle = FMenuCoreStyle::Get().GetWidgetStyle<FRadioButtonsStyle>(FName("WS_RadioButtonsStyle"));
	}

}

void UHASMenuAddContentWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	/*if (RadioButtonsHost)
	{
		RadioButtonsHost->SetContent(SNew(SHASSlateRadioButton));
	}*/
}

UButton* UHASMenuAddContentWidget::GetBackToMenuButton()
{
	if (BackToMenuButton)
	{
		return BackToMenuButton;
	}
	return nullptr;
}


void UHASMenuAddContentWidget::SetWidgetStyle()
{
	if (!bIsDarkTheme)
	{
		WidgetStyle = FMenuCoreStyle::Get().GetWidgetStyle<FMenuDefaultStyle>("WS_MenuDefault");
	}
	else
	{
		WidgetStyle = FMenuCoreStyle::Get().GetWidgetStyle<FMenuDefaultStyle>("WS_MenuDark");
	}
}

void UHASMenuAddContentWidget::SetMenuTheme(FMenuDefaultStyle MenuWidgetStyle)
{
	if (ThemeImage)
	{
		if (!bIsDarkTheme)
		{
			ThemeImage->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f));
		}
		else
		{
			ThemeImage->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 0.4f));
		}
	}

	if (BackToMenuButton)
	{
		BackToMenuButton->WidgetStyle = MenuWidgetStyle.ButtonStyle;
		if (BackToMenuText)
		{
			BackToMenuText->SetText(FText::FromString("Back"));
			BackToMenuText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
			BackToMenuText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
		}
	}

	if (DefaultSettingsButton)
	{
		DefaultSettingsButton->WidgetStyle = MenuWidgetStyle.ButtonStyle;
		if (DefaultSettingsText)
		{
			DefaultSettingsText->SetText(FText::FromString("Default"));
			DefaultSettingsText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
			DefaultSettingsText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
		}
	}

	if (ApplySettingsButton)
	{
		ApplySettingsButton->WidgetStyle = MenuWidgetStyle.ButtonStyle;
		if (ApplySettingsText)
		{
			ApplySettingsText->SetText(FText::FromString("Apply"));
			ApplySettingsText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
			ApplySettingsText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
		}
	}
}
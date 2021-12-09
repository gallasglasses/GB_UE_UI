// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/HASMenuSettingsWidget.h"
#include "Menu/UI/Styles/MenuCoreStyle.h"
#include "Menu/UI/Styles/MenuDefaultWidgetStyle.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UHASMenuSettingsWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetWidgetStyle();
	SetMenuTheme(WidgetStyle);
}

void UHASMenuSettingsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetWidgetStyle();
	SetMenuTheme(WidgetStyle);

	if (GeneralSettingsButton)
	{
		GeneralSettingsButton->OnClicked.AddDynamic(this, &UHASMenuSettingsWidget::OnGeneralSettingsClicked);
	}

	if (GameplaySettingsButton)
	{
		GameplaySettingsButton->OnClicked.AddDynamic(this, &UHASMenuSettingsWidget::OnGameplaySettingsClicked);
	}

	if (GraphicsSettingsButton)
	{
		GraphicsSettingsButton->OnClicked.AddDynamic(this, &UHASMenuSettingsWidget::OnGraphicsSettingsClicked);
	}

	if (SoundSettingsButton)
	{
		SoundSettingsButton->OnClicked.AddDynamic(this, &UHASMenuSettingsWidget::OnSoundSettingsClicked);
	}
}

void UHASMenuSettingsWidget::OnGeneralSettingsClicked()
{
	SettingsWidgetSwitcher->SetActiveWidgetIndex(0);
}

void UHASMenuSettingsWidget::OnGameplaySettingsClicked()
{
	SettingsWidgetSwitcher->SetActiveWidgetIndex(1);
}

void UHASMenuSettingsWidget::OnGraphicsSettingsClicked()
{
	SettingsWidgetSwitcher->SetActiveWidgetIndex(2);
}

void UHASMenuSettingsWidget::OnSoundSettingsClicked()
{
	SettingsWidgetSwitcher->SetActiveWidgetIndex(3);
}

UButton* UHASMenuSettingsWidget::GetBackToMenuButton() 
{
	if (BackToMenuButton)
	{
		return BackToMenuButton;
	}
	return nullptr;
}

void UHASMenuSettingsWidget::SetFirstActiveWidgetIndex()
{
	if (SettingsWidgetSwitcher->GetActiveWidgetIndex() != 0)
	{
		SettingsWidgetSwitcher->SetActiveWidgetIndex(0);
	}
}

void UHASMenuSettingsWidget::SetWidgetStyle()
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

void UHASMenuSettingsWidget::SetMenuTheme(FMenuDefaultStyle MenuWidgetStyle)
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

	if (GeneralSettingsButton)
	{
		GeneralSettingsButton->WidgetStyle = MenuWidgetStyle.ButtonStyle;
		if (GeneralSettingsText)
		{
			GeneralSettingsText->SetText(FText::FromString("GENERAL"));
			GeneralSettingsText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
			GeneralSettingsText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
		}
	}

	if (GameplaySettingsButton)
	{
		GameplaySettingsButton->WidgetStyle = MenuWidgetStyle.ButtonStyle;
		if (GameplaySettingsText)
		{
			GameplaySettingsText->SetText(FText::FromString("GAMEPLAY"));
			GameplaySettingsText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
			GameplaySettingsText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
		}
	}

	if (GraphicsSettingsButton)
	{
		GraphicsSettingsButton->WidgetStyle = MenuWidgetStyle.ButtonStyle;
		if (GraphicsSettingsText)
		{
			GraphicsSettingsText->SetText(FText::FromString("GRAPHICS"));
			GraphicsSettingsText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
			GraphicsSettingsText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
		}
	}

	if (SoundSettingsButton)
	{
		SoundSettingsButton->WidgetStyle = MenuWidgetStyle.ButtonStyle;
		if (SoundSettingsText)
		{
			SoundSettingsText->SetText(FText::FromString("SOUND"));
			SoundSettingsText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
			SoundSettingsText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
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
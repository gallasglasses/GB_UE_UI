// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/HASMenuWidget.h"
#include "Menu/UI/HASMenuSettingsWidget.h"
#include "Menu/UI/HASMenuAddContentWidget.h"
#include "Menu/UI/HASMenuQuitWidget.h"
#include "Menu/UI/Styles/MenuCoreStyle.h"
#include "Menu/UI/Styles/MenuDefaultWidgetStyle.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CheckBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UHASMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetWidgetStyle();
	SetMenuTheme(WidgetStyle);
}

void UHASMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (NewGameButton)
	{
		NewGameButton->OnClicked.AddDynamic(this, &UHASMenuWidget::OnStartGameClicked);
	}

	if (SettingsButton)
	{
		SettingsButton->OnClicked.AddDynamic(this, &UHASMenuWidget::OnSettingsClicked);
	}

	if (AdditionalContentButton)
	{
		AdditionalContentButton->OnClicked.AddDynamic(this, &UHASMenuWidget::OnAddContentClicked);
	}

	if (CreditButton)
	{
		CreditButton->OnClicked.AddDynamic(this, &UHASMenuWidget::OnCreditClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UHASMenuWidget::OnQuitClicked);
	}

	if (SettingsWidget)
	{
		if (SettingsWidget->GetBackToMenuButton())
		{
			SettingsWidget->GetBackToMenuButton()->OnClicked.AddDynamic(this, &UHASMenuWidget::OnBackSettingsToMenuClicked);
		}
	}
	
	if (AddContentWidget)
	{
		if (AddContentWidget->GetBackToMenuButton())
		{
			AddContentWidget->GetBackToMenuButton()->OnClicked.AddDynamic(this, &UHASMenuWidget::OnBackAddContentToMenuClicked);
		}
	}
}

void UHASMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	DarkThemeCheckBox = Cast<UCheckBox>(GetWidgetFromName("DarkThemeCheckBox"));

	if (!DarkThemeCheckBox->OnCheckStateChanged.IsBound())
	{
		DarkThemeCheckBox->OnCheckStateChanged.AddDynamic(this, &UHASMenuWidget::OnChecked);
	}

	SetMenuTheme(WidgetStyle);
}

void UHASMenuWidget::OnStartGameClicked()
{
	const FName	StartUpLevelName = "TestLevel";
	UGameplayStatics::OpenLevel(this, StartUpLevelName);
}

void UHASMenuWidget::OnSettingsClicked()
{
	CanvasPanel->SetVisibility(ESlateVisibility::Hidden);
	SettingsWidget->SetVisibility(ESlateVisibility::Visible);
}

void UHASMenuWidget::OnAddContentClicked()
{
	CanvasPanel->SetVisibility(ESlateVisibility::Hidden);
	AddContentWidget->SetVisibility(ESlateVisibility::Visible);
}

void UHASMenuWidget::OnCreditClicked()
{
	
}

void UHASMenuWidget::OnQuitClicked()
{
	QuitWidget->SetVisibility(ESlateVisibility::Visible);
}

void UHASMenuWidget::OnChecked(bool bIsChecked)
{
	bIsDarkTheme = bIsChecked;
	SetWidgetStyle();

	SettingsWidget->bIsDarkTheme = bIsChecked;
	SettingsWidget->SetWidgetStyle();
	SettingsWidget->SetMenuTheme(WidgetStyle);

	AddContentWidget->bIsDarkTheme = bIsChecked;
	AddContentWidget->SetWidgetStyle();
	AddContentWidget->SetMenuTheme(WidgetStyle);

	QuitWidget->bIsDarkTheme = bIsChecked;
	QuitWidget->SetWidgetStyle();
	QuitWidget->SetMenuTheme(WidgetStyle);
}

void UHASMenuWidget::OnBackSettingsToMenuClicked()
{
	SettingsWidget->SetFirstActiveWidgetIndex();
	SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
	CanvasPanel->SetVisibility(ESlateVisibility::Visible);
}

void UHASMenuWidget::OnBackAddContentToMenuClicked()
{
	AddContentWidget->SetVisibility(ESlateVisibility::Hidden);
	CanvasPanel->SetVisibility(ESlateVisibility::Visible);
}

void UHASMenuWidget::SetWidgetStyle()
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

void UHASMenuWidget::SetMenuTheme(FMenuDefaultStyle MenuWidgetStyle)
{
	if (DarkThemeImage)
	{
		if (!bIsDarkTheme)
		{
			DarkThemeImage->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f));
		}
		else
		{
			DarkThemeImage->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 0.4f));
		}
	}

	if (NewGameButton)
	{
		NewGameButton->WidgetStyle = MenuWidgetStyle.ButtonStyle;
		if (NewGameText)
		{
			NewGameText->SetText(FText::FromString("NEW GAME"));
			NewGameText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
			NewGameText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
		}
	}

	if (SettingsButton)
	{
		SettingsButton->WidgetStyle = MenuWidgetStyle.ButtonStyle;
		if (SettingsText)
		{
			SettingsText->SetText(FText::FromString("SETTINGS"));
			SettingsText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
			SettingsText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
		}
	}

	if (AdditionalContentButton)
	{
		AdditionalContentButton->WidgetStyle = MenuWidgetStyle.ButtonStyle;
		if (AdditionalContentText)
		{
			AdditionalContentText->SetText(FText::FromString("ADDITIONAL CONTENT"));
			AdditionalContentText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
			AdditionalContentText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
		}
	}

	if (CreditButton)
	{
		CreditButton->WidgetStyle = MenuWidgetStyle.ButtonStyle;
		if (CreditText)
		{
			CreditText->SetText(FText::FromString("CREDIT"));
			CreditText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
			CreditText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
		}
	}

	if (QuitButton)
	{
		QuitButton->WidgetStyle = MenuWidgetStyle.ButtonStyle;
		if (QuitText)
		{
			QuitText->SetText(FText::FromString("QUIT"));
			QuitText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
			QuitText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
		}
	}

	if (DarkThemeCheckBox)
	{
		if (DarkThemeText)
		{
			DarkThemeText->SetText(FText::FromString("DARK THEME"));
			DarkThemeText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
			DarkThemeText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
		}
	}
}
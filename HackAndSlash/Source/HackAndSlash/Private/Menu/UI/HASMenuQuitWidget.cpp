// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/HASMenuQuitWidget.h"
#include "Menu/UI/Styles/MenuCoreStyle.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/KismetSystemLibrary.h"

void UHASMenuQuitWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetWidgetStyle();
	SetMenuTheme(WidgetStyle);
}

void UHASMenuQuitWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetWidgetStyle();
	SetMenuTheme(WidgetStyle);

	if (YesButton)
	{
		YesButton->OnClicked.AddDynamic(this, &UHASMenuQuitWidget::OnYesQuitClicked);
	}

	if (NoButton)
	{
		NoButton->OnClicked.AddDynamic(this, &UHASMenuQuitWidget::OnNoQuitClicked);
	}
}

void UHASMenuQuitWidget::OnYesQuitClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UHASMenuQuitWidget::OnNoQuitClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}

//void UHASMenuQuitWidget::SetIsThemeDark(bool bIsDark)
//{
//	bIsDarkTheme = bIsDark;
//}

void UHASMenuQuitWidget::SetWidgetStyle()
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

void UHASMenuQuitWidget::SetMenuTheme(FMenuDefaultStyle MenuWidgetStyle)
{
	if (ThemeImage)
	{
		if (!bIsDarkTheme)
		{
			ThemeImage->SetColorAndOpacity(FLinearColor(0.010960f, 0.023153f, 0.078187f, 0.6f));
		}
		else
		{
			ThemeImage->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 0.6f));
		}
	}

	if (YesButton)
	{
		YesButton->WidgetStyle = MenuWidgetStyle.ButtonStyle;
		if (YesText)
		{
			YesText->SetText(FText::FromString("YES"));
			YesText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
			YesText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
		}
	}

	if (NoButton)
	{
		NoButton->WidgetStyle = MenuWidgetStyle.ButtonStyle;
		if (NoText)
		{
			NoText->SetText(FText::FromString("NO"));
			NoText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
			NoText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
		}
	}

	if (QuestionText)
	{
		QuestionText->SetText(FText::FromString("DO YOU WANT QUIT?"));
		QuestionText->SetColorAndOpacity(MenuWidgetStyle.TextButtonStyle.ColorAndOpacity);
		QuestionText->SetFont(MenuWidgetStyle.TextButtonStyle.Font);
	}
}
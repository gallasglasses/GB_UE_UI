// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/HASMenuSettingsWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void UHASMenuSettingsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

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
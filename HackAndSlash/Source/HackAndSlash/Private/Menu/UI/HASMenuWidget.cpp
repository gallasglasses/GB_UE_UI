// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/HASMenuWidget.h"
#include "Menu/UI/HASMenuSettingsWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UHASMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UHASMenuWidget::OnStartGameClicked);
	}

	if (SettingsButton)
	{
		SettingsButton->OnClicked.AddDynamic(this, &UHASMenuWidget::OnSettingsClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UHASMenuWidget::OnQuitClicked);
	}

	if (SettingsWidget)
	{
		if (SettingsWidget->GetBackToMenuButton())
		{
			SettingsWidget->GetBackToMenuButton()->OnClicked.AddDynamic(this, &UHASMenuWidget::OnBackToMenuClicked);
		}
	}
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

void UHASMenuWidget::OnQuitClicked()
{
	QuitWidget->SetVisibility(ESlateVisibility::Visible);
}

void UHASMenuWidget::OnBackToMenuClicked()
{
	SettingsWidget->SetFirstActiveWidgetIndex();
	SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
	CanvasPanel->SetVisibility(ESlateVisibility::Visible);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/HASMenuQuitWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UHASMenuQuitWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

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
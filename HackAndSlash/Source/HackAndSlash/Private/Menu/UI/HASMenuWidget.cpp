// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/HASMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UHASMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UHASMenuWidget::OnStartGame);
	}
}

void UHASMenuWidget::OnStartGame()
{
	const FName	StartUpLevelName = "TestLevel";
	UGameplayStatics::OpenLevel(this, StartUpLevelName);
}

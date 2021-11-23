// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HASGameHUD.h"
#include "Blueprint/UserWidget.h"

void AHASGameHUD::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}
}
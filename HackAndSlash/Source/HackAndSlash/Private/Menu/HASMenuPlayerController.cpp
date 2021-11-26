// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/HASMenuPlayerController.h"

void AHASMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/HASMenuGameModeBase.h"
#include "Menu/HASMenuPlayerController.h"
#include "Menu/UI/HASMenuHUD.h"

AHASMenuGameModeBase::AHASMenuGameModeBase()
{
	PlayerControllerClass = AHASMenuPlayerController::StaticClass();
	HUDClass = AHASMenuHUD::StaticClass();
}
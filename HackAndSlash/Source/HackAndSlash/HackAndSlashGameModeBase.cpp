// Copyright Epic Games, Inc. All Rights Reserved.


#include "HackAndSlashGameModeBase.h"
#include "Player/HASBaseCharacter.h"
#include "Player/HASPlayerController.h"

AHackAndSlashGameModeBase::AHackAndSlashGameModeBase()
{
	DefaultPawnClass = AHASBaseCharacter::StaticClass();
	PlayerControllerClass = AHASPlayerController::StaticClass();
}


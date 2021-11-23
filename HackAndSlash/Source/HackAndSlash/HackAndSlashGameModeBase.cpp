// Copyright Epic Games, Inc. All Rights Reserved.


#include "HackAndSlashGameModeBase.h"
#include "Player/HASBaseCharacter.h"
#include "Player/HASPlayerController.h"
#include "UI/HASGameHUD.h"

AHackAndSlashGameModeBase::AHackAndSlashGameModeBase()
{
	DefaultPawnClass = AHASBaseCharacter::StaticClass();
	PlayerControllerClass = AHASPlayerController::StaticClass();
	HUDClass = AHASGameHUD::StaticClass();
}

//void AHackAndSlashGameModeBase::SetMatchState(EHASMatchState State)
//{
//	if (MatchState == State)
//	{
//		return;
//	}
//	MatchState = State;
//	OnMatchStateChanged.Broadcast(MatchState);
//}
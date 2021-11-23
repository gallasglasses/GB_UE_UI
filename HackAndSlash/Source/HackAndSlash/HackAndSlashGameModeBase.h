// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/HASGameHUD.h"
#include "HackAndSlashGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API AHackAndSlashGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AHackAndSlashGameModeBase();

// 	FOnMatchStateChangedSignature OnMatchStateChanged;
// 
// private:
// 	EHASMatchState MatchState = EHASMatchState::WaitingToStart;
// 
// 	void SetMatchState(EHASMatchState State);
};

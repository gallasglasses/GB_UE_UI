// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSystem/HASSaveGame.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void UHASSaveGame::CollectData(UWorld* World)
{
	FMemoryWriter MemoryWriter(Bytes, true);
	FObjectAndNameAsStringProxyArchive Ar(MemoryWriter, true);
	Ar.ArIsSaveGame = true;

	if (APawn* SavePawn = World->GetFirstPlayerController()->GetPawn())
	{
		SavePawn->Serialize(Ar);
	}

	/*if (USaveSystemSubsystem* SaveSystemSubsystem = World->GetSubsystem<USaveSystemSubsystem>())
	{
		SaveSystemSubsystem->Serialize(Ar);
	}*/
}

void UHASSaveGame::ApplyData(UWorld* World)
{
	FMemoryWriter MemoryWriter(Bytes, true);
	FObjectAndNameAsStringProxyArchive Ar(MemoryWriter, true);
	Ar.ArIsSaveGame = true;

	if (APawn* SavePawn = World->GetFirstPlayerController()->GetPawn())
	{
		SavePawn->Serialize(Ar);
	}

	/*if (USaveSystemSubsystem* SaveSystemSubsystem = World->GetSubsystem<USaveSystemSubsystem>())
	{
		SaveSystemSubsystem->Serialize(Ar);
	}*/
}

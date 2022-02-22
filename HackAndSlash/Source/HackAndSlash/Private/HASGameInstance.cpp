// Fill out your copyright notice in the Description page of Project Settings.

#include "HASGameInstance.h"
#include "SaveManager.h"
#include "Kismet/GameplayStatics.h"

void UHASGameInstance::Init()
{
	Super::Init();

	GLog->Log(ELogVerbosity::Warning, TEXT("HASGameInstance::Init Success"));

	SaveManager = NewObject<USaveManager>(this);
	SaveManager->Init();
}

USaveManager* UHASGameInstance::GetSaveManager(UObject* WorldContextObject)
{
	auto* MyInstance = Cast<UHASGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	return MyInstance ? MyInstance->SaveManager : nullptr;
}

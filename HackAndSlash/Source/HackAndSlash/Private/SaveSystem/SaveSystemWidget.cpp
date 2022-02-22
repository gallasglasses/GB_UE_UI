// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSystem/SaveSystemWidget.h"
#include "Kismet/GameplayStatics.h"
#include "SaveSystemSubsystem.h"
#include "SaveManager.h"
#include "HASGameInstance.h"
#include "HASSaveGame.h"

void USaveSystemWidget::SaveLootsData()
{
	auto GameInstance = Cast<UHASGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	auto SaveManager = GameInstance->GetSaveManager(GetWorld());
	auto CurrentSave = SaveManager->GetCurrentSave();
	auto Subsystem = GetWorld()->GetSubsystem<USaveSystemSubsystem>();

	auto Loots = Subsystem->GetLoots();
	for (auto Loot : Loots)
	{
		CurrentSave->LootSaveData.Add(Loot.Key, Loot.Value->GetLootData());
	}
}

void USaveSystemWidget::LoadLootsData()
{
	auto GameInstance = Cast<UHASGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	auto SaveManager = GameInstance->GetSaveManager(GetWorld());
	auto CurrentSave = SaveManager->GetCurrentSave();
	auto Subsystem = GetWorld()->GetSubsystem<USaveSystemSubsystem>();

	auto Loots = Subsystem->GetLoots();
	for (auto Loot : Loots)
	{
		for (auto LootData : CurrentSave->LootSaveData)
		{
			if (Loot.Key == LootData.Key)
			{
				if (auto LootBox = Cast<AHASLootBox>(Loot.Value))
				{
					LootBox->SetLootData(LootData.Value);
				}
			}
		}

	}
}

#include "SaveManager.h"
#include "HASSaveGame.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"

void USaveManager::Init()
{
	CurrentSave = Cast<UHASSaveGame>(UGameplayStatics::CreateSaveGameObject(UHASSaveGame::StaticClass()));

	const FString SlotsPath = FPaths::ProjectSavedDir() + "SaveGames/Slots.txt";

	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	if (FileManager.FileExists(*SlotsPath))
	{
		if (FFileHelper::LoadFileToStringArray(CurrentSlots, *SlotsPath))
		{
			for (const auto& Slot : CurrentSlots)
			{
				GLog->Log(ELogVerbosity::Warning, TEXT("SaveManager::Init, slot: ") + Slot);
			}
		}
	}
}

bool USaveManager::IsSaveGameExist(const FString& SlotName) const
{
	return UGameplayStatics::DoesSaveGameExist(SlotName, 0);

	//PURE
	//Func(PureFunc());
	//Func2(PureFunc());

	//NON PURE
	//var int = NonPure();
	//Func(int);
	//Func2(int);
}

void USaveManager::LoadGame(const FString& SlotName)
{
	//if (!IsSaveGameExist(SlotName))
	//{
	//	return;
	//}
	// 
	//FAsyncLoadGameFromSlotDelegate LoadDelegate;
	//LoadDelegate.BindUObject(this, &ThisClass::OnGameLoadedFunc);

	//UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0, LoadDelegate);

	const FString JsonPath = FPaths::ProjectSavedDir() + "SaveGames/TestFloat.json";

	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	if (FileManager.FileExists(*JsonPath))
	{
		FString JsonString;
		FFileHelper::LoadFileToString(JsonString, *JsonPath);

		FJsonSave JsonSave;
		FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &JsonSave, 0, 0);

		CurrentSave->TestFloat = JsonSave.TestFloat;
		CurrentSave->CharacterSaveData = JsonSave.CharacterSaveData;
		CurrentSave->LootSaveData = JsonSave.LootSaveData;
	}

	OnGameLoadedFunc(TEXT("JsonSave"), 0, CurrentSave);
}

void USaveManager::SaveGame(const FString& SlotName)
{
	/*FAsyncSaveGameToSlotDelegate SaveDelegate;
	SaveDelegate.BindUObject(this, &ThisClass::OnGameSavedFunc);

	UGameplayStatics::AsyncSaveGameToSlot(CurrentSave, SlotName, 0, SaveDelegate);*/

	FJsonSave JsonSave;
	JsonSave.TestFloat = CurrentSave->TestFloat;
	JsonSave.CharacterSaveData = CurrentSave->CharacterSaveData;
	JsonSave.LootSaveData = CurrentSave->LootSaveData;

	FString JsonString;
	FJsonObjectConverter::UStructToJsonObjectString(JsonSave, JsonString);

	const FString JsonPath = FPaths::ProjectSavedDir() + "SaveGames/TestFloat.json";
	FFileHelper::SaveStringToFile(JsonString, *JsonPath);

	OnGameSavedFunc(TEXT("Json"), 0, true);
}

void USaveManager::OnGameLoadedFunc(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame)
{
	CurrentSave = Cast<UHASSaveGame>(SaveGame);
	OnGameLoaded.Broadcast(SlotName);
}

void USaveManager::OnGameSavedFunc(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	if (!CurrentSlots.Contains(SlotName))
	{
		CurrentSlots.AddUnique(SlotName);
		SaveCurrentSlots();
	}
	
	OnGameSaved.Broadcast(SlotName);
}

void USaveManager::SaveCurrentSlots() const
{
	const FString SlotsPath = FPaths::ProjectSavedDir() + "SaveGames/Slots.txt";

	if (FFileHelper::SaveStringArrayToFile(CurrentSlots, *SlotsPath))
	{
		GLog->Log(ELogVerbosity::Warning, TEXT("SaveManager::SaveCurrentSlots, save success"));
	}
}
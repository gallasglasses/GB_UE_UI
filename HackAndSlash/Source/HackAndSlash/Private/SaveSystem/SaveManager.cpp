#include "SaveManager.h"
#include "HASSaveGame.h"
#include "Kismet/GameplayStatics.h"

void USaveManager::Init()
{
	CurrentSave = Cast<UHASSaveGame>(UGameplayStatics::CreateSaveGameObject(UHASSaveGame::StaticClass()));
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
	if (!IsSaveGameExist(SlotName))
	{
		return;
	}

	//CurrentSave = Cast<UHASSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

	FAsyncLoadGameFromSlotDelegate LoadDelegate;
	LoadDelegate.BindUObject(this, &ThisClass::OnGameLoadedFunc);

	UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0, LoadDelegate);
}

void USaveManager::SaveGame(const FString& SlotName)
{
	//UGameplayStatics::SaveGameToSlot(CurrentSave, SlotName, 0);

	FAsyncSaveGameToSlotDelegate SaveDelegate;
	SaveDelegate.BindUObject(this, &ThisClass::OnGameSavedFunc);

	UGameplayStatics::AsyncSaveGameToSlot(CurrentSave, SlotName, 0, SaveDelegate);
}

void USaveManager::OnGameLoadedFunc(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame)
{
	CurrentSave = Cast<UHASSaveGame>(SaveGame);
	OnGameLoaded.Broadcast(SlotName);
}

void USaveManager::OnGameSavedFunc(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	OnGameSaved.Broadcast(SlotName);
}

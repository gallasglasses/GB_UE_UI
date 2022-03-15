#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveData.h"
#include "SaveManager.generated.h"

class USaveGame;
class UHASSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveAction, const FString&, SlotName);

USTRUCT()
struct FJsonSave 
{
	GENERATED_BODY()

	UPROPERTY()
	float TestFloat;

	UPROPERTY()
	FCharacterSaveData CharacterSaveData;

	UPROPERTY()
	TMap<FName, FLootSaveData> LootSaveData;

};

UCLASS()
class HACKANDSLASH_API USaveManager : public UObject
{
	GENERATED_BODY()

public:

	virtual UWorld* GetWorld() const override
	{
		return HasAnyFlags(RF_ClassDefaultObject) ? nullptr : GetOuter()->GetWorld();
	}

	UPROPERTY(BlueprintAssignable)
		FOnSaveAction OnGameSaved;

	UPROPERTY(BlueprintAssignable)
		FOnSaveAction OnGameLoaded;

	void Init();

	UFUNCTION(BlueprintPure)
		bool IsSaveGameExist(const FString& SlotName) const;

	UFUNCTION(BlueprintCallable)
		void LoadGame(const FString& SlotName);

	UFUNCTION(BlueprintCallable)
		void SaveGame(const FString& SlotName);

	UHASSaveGame* GetCurrentSave() const { return  CurrentSave; }

	UFUNCTION(BlueprintCallable)
		TArray<FString> GetCurrentSlots() const { return  CurrentSlots; }

protected:

	void OnGameLoadedFunc(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame);

	void OnGameSavedFunc(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	UPROPERTY(BlueprintReadWrite)
		UHASSaveGame* CurrentSave;

	TArray<FString> CurrentSlots;

	void SaveCurrentSlots() const;
};
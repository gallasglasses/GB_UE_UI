// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FToolBarBuilder;
class FMenuBuilder;
class AQuest;
class STableViewBase;
class ITableRow;

class FESWSystemModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

	void AddMenuExtension(FMenuBuilder& Build);

	void AddToolbarExtension(FToolBarBuilder& Build);

	static TSharedRef<SWidget> GetRowHeader(FString Text);
	
private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;

	TArray<AQuest*> Quests;

	TSharedRef<ITableRow> GenerateQuestRow(AQuest* Quest, const TSharedRef<STableViewBase>& Table);

	void UpdateQuests();
	
	void UpdateQuestsList();

	void TabClosed(TSharedRef<SDockTab> Tab);

	TSharedPtr<SListView<AQuest*>> QuestsList;
	
	TSharedPtr<SBox> ObjectivesHolder;
};

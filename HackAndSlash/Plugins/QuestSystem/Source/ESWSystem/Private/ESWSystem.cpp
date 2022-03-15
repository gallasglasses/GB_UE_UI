// Copyright Epic Games, Inc. All Rights Reserved.

#include "ESWSystem.h"
#include "ESWSystemStyle.h"
#include "ESWSystemCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "Engine/Selection.h"
#include "QuestSystem/Public/Quest.h"
#include "SQuestListView.h"

static const FName ESWSystemTabName("ESWSystem");

#define LOCTEXT_NAMESPACE "FESWSystem"

void FESWSystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FESWSystemStyle::Initialize();
	FESWSystemStyle::ReloadTextures();

	FESWSystemCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FESWSystemCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FESWSystemModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FESWSystemModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ESWSystemTabName, FOnSpawnTab::CreateRaw(this, &FESWSystemModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FESWSystemTabTitle", "ESWSystem"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	TSharedPtr<FExtender> MenuExtender = MakeShareable( new FExtender());
	MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands,
		FMenuExtensionDelegate::CreateRaw(this, &FESWSystemModule::AddMenuExtension));

	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);

	TSharedPtr<FExtender> ToolbarExtender = MakeShareable( new FExtender());
	ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands,
		FToolBarExtensionDelegate::CreateRaw(this, &FESWSystemModule::AddToolbarExtension));

	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}

void FESWSystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FESWSystemStyle::Shutdown();

	FESWSystemCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ESWSystemTabName);
}

TSharedRef<SDockTab> FESWSystemModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::FromString(TEXT("Move Objects"));
	
	UpdateQuests();

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.OnTabClosed_Raw(this, &FESWSystemModule::TabClosed)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SButton)
					.OnPressed_Raw(this, &FESWSystemModule::UpdateQuestsList)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Update quest list from selection"))
					]
				]
				+ SVerticalBox::Slot()
				.FillHeight(1.f)
				[
					SNew(SBox)
					[
						SAssignNew(QuestsList, SListView<AQuest*>)
						.ItemHeight(24)
						.ListItemsSource(&Quests)
						.OnGenerateRow_Raw(this, &FESWSystemModule::GenerateQuestRow)
						.HeaderRow
						(
							SNew(SHeaderRow)
							+ SHeaderRow::Column("Name")[GetRowHeader("Name")]
							+ SHeaderRow::Column("Description")[GetRowHeader("Description")]
							+ SHeaderRow::Column("IsStory")[GetRowHeader("Is Story")]
							+ SHeaderRow::Column("Objectives")[GetRowHeader("Objectives")]
							+ SHeaderRow::Column("KeepOrder")[GetRowHeader("Keep Order")]
							+ SHeaderRow::Column("PreviousQuest")[GetRowHeader("Previous Quest")]
						)
					]
				]
				+ SVerticalBox::Slot()
				.FillHeight(1.f)
				[
					SAssignNew(ObjectivesHolder, SBox)
				]
			]
		];
}

TSharedRef<ITableRow> FESWSystemModule::GenerateQuestRow(AQuest* Quest,
	const TSharedRef<STableViewBase>& Table)
{
	return SNew(SQuestListView, Table)
		.Quest(Quest)
		.ObjectivesHolder(ObjectivesHolder);
}

TSharedRef<SWidget> FESWSystemModule::GetRowHeader(FString Text)
{
	return SNew(SBorder)
		.HAlign(HAlign_Center)
		.Padding(1.f)
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString(Text))
		];
}

void FESWSystemModule::UpdateQuests()
{
	Quests.Empty();
	for (FSelectionIterator Iter(*GEditor->GetSelectedActors()); Iter; ++Iter)
	{
		if (auto* Quest = Cast<AQuest>(*Iter))
		{
			Quests.AddUnique(Quest);
		}
	}

	if (Quests.Num() > 0)
	{
		GEditor->SelectNone(true, true);
		for (auto* Quest : Quests)
		{
			GEditor->SelectActor(Quest, true, false);
		}
	}
}

void FESWSystemModule::UpdateQuestsList()
{
	ObjectivesHolder->SetContent(SNullWidget::NullWidget);
	UpdateQuests();
	QuestsList->RequestListRefresh();
}

void FESWSystemModule::TabClosed(TSharedRef<SDockTab> Tab)
{
	ObjectivesHolder.Reset();
	QuestsList.Reset();
}

void FESWSystemModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(ESWSystemTabName);
}

void FESWSystemModule::AddMenuExtension(FMenuBuilder& Build)
{
	Build.AddMenuEntry(FESWSystemCommands::Get().OpenPluginWindow);
}

void FESWSystemModule::AddToolbarExtension(FToolBarBuilder& Build)
{
	Build.AddToolBarButton(FESWSystemCommands::Get().OpenPluginWindow);
}

void FESWSystemModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	/*{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FESWSystemCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}*/

	/*{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FESWSystemCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}*/
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FESWSystemModule, ESWSystem)
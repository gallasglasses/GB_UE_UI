// Fill out your copyright notice in the Description page of Project Settings.


#include "SQuestListView.h"

#include <basetyps.h>

#include "ISinglePropertyView.h"
#include "SlateOptMacros.h"
#include "ESWSystem.h"
#include "ESWSystemCommands.h"
#include "Widgets/Layout/SWrapBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedRef<SWidget> SQuestListView::GenerateWidgetForColumn(const FName& InColumnName)
{
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
 
	FSinglePropertyParams Params;
	Params.NamePlacement = EPropertyNamePlacement::Hidden;
	
	if (InColumnName == "Name")
	{
		return SNew(SBox)
			[
				PropertyModule.CreateSingleProperty(Quest,GET_MEMBER_NAME_CHECKED(AQuest, Name), Params).ToSharedRef()
			];
	}

	if (InColumnName == "Description")
	{
		return SNew(SBox)
			[
				PropertyModule.CreateSingleProperty(Quest,GET_MEMBER_NAME_CHECKED(AQuest, Description), Params).ToSharedRef()
			];
	}

	if (InColumnName == "IsStory")
	{
		return SNew(SBox)
			[
				PropertyModule.CreateSingleProperty(Quest,GET_MEMBER_NAME_CHECKED(AQuest, bIsStoryQuest), Params).ToSharedRef()
			];
	}

	if (InColumnName == "Objectives")
	{
		return SNew(SBox)
			[
				SNew(SButton)
				.OnPressed_Raw(this, &SQuestListView::OpenObjectives)
				[
					SNew(SBox)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Show objectives"))
					]
				]
			];
	}

	if (InColumnName == "KeepOrder")
	{
		return SNew(SBox)
			[
				PropertyModule.CreateSingleProperty(Quest,GET_MEMBER_NAME_CHECKED(AQuest, bKeepObjectivesOrder), Params).ToSharedRef()
			];
	}

	if (InColumnName == "PreviousQuest")
	{
		return SNew(SBox)
			[
				PropertyModule.CreateSingleProperty(Quest,GET_MEMBER_NAME_CHECKED(AQuest, PreviousQuest), Params).ToSharedRef()
			];
	}

	return SNew(SBox)[SNew(STextBlock).Text(FText::FromString("Wrong field"))];
}

void SQuestListView::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)
{
	Quest = InArgs._Quest;
	ObjectivesHolder = InArgs._ObjectivesHolder;
	FSuperRowType::Construct(FSuperRowType::FArguments(), InOwnerTableView);
}

void SQuestListView::OpenObjectives()
{
	ObjectivesHolder->SetContent(
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		[
			SNew(SWrapBox)
			.Orientation(EOrientation::Orient_Horizontal)
			+ SWrapBox::Slot()[GetCreateObjectiveButton(EObjectiveType::Ot_Interact)]
			+ SWrapBox::Slot()[GetCreateObjectiveButton(EObjectiveType::Ot_Location)]
			+ SWrapBox::Slot()[GetCreateObjectiveButton(EObjectiveType::Ot_Collect)]
		]
		+ SVerticalBox::Slot()
		[
			SNew(SBox)
			[
				SAssignNew(ObjectivesList, SListView<UObjective*>)
				.ItemHeight(24)
				.ListItemsSource(&Quest->GetObjectives())
				.OnGenerateRow_Raw(this, &SQuestListView::GenerateObjectiveRow)
				.HeaderRow
				(
					SNew(SHeaderRow)
					+ SHeaderRow::Column("Description")[FESWSystemModule::GetRowHeader("Description")]
					+ SHeaderRow::Column("Type")[FESWSystemModule::GetRowHeader("Type")]
					+ SHeaderRow::Column("Target")[FESWSystemModule::GetRowHeader("Target")]
					+ SHeaderRow::Column("TargetCount")[FESWSystemModule::GetRowHeader("TargetCount")]
					//+ SHeaderRow::Column("CollectCount")[FESWSystemModule::GetRowHeader("CollectCount")]
					+ SHeaderRow::Column("Delete")[FESWSystemModule::GetRowHeader("Delete")]
					+ SHeaderRow::Column("Move")[FESWSystemModule::GetRowHeader("Move")]
				)
			]
		]
	);
}

TSharedRef<ITableRow> SQuestListView::GenerateObjectiveRow(UObjective* Objective, const TSharedRef<STableViewBase>& Table)
{
	return SNew(SObjectiveTableRow, Table)
	.Objective(Objective)
	.Quest(Quest);
}

TSharedRef<SWidget> SQuestListView::GetCreateObjectiveButton(EObjectiveType Type)
{
	FString TypeName;
	switch (Type)
	{
	case EObjectiveType::Ot_Interact: TypeName = "Interact"; break;
	case EObjectiveType::Ot_Location: TypeName = "Location"; break;
	case EObjectiveType::Ot_Collect: TypeName = "Collect"; break;
	default: return SNullWidget::NullWidget;
	}
	
	return SNew(SButton)
	.OnPressed_Raw(this, &SQuestListView::AddObjective, Type)
	[
		SNew(STextBlock)
		.Text(FText::FromString("Add " + TypeName + " objective"))
	];
}

void SQuestListView::AddObjective(EObjectiveType Type)
{
	switch (Type)
	{
	case EObjectiveType::Ot_Interact: Quest->AddInteractObjective(); break;
	case EObjectiveType::Ot_Location: Quest->AddLocationObjective(); break;
	case EObjectiveType::Ot_Collect: Quest->AddCollectionObjective(); break;
	default: return;
	}

	ObjectivesList->RequestListRefresh();
}

TSharedRef<SWidget> SObjectiveTableRow::GenerateWidgetForColumn(const FName& InColumnName)
{
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
 
	FSinglePropertyParams Params;
	Params.NamePlacement = EPropertyNamePlacement::Hidden;
	
	if (InColumnName == "Description")
	{
		return SNew(SBox)
			[
				PropertyModule.CreateSingleProperty(Objective,GET_MEMBER_NAME_CHECKED(UObjective, Description), Params).ToSharedRef()
			];
	}

	if (InColumnName == "Type")
	{
		return SNew(SBox)
			.IsEnabled(false)
			[
				PropertyModule.CreateSingleProperty(Objective,GET_MEMBER_NAME_CHECKED(UObjective, Type), Params).ToSharedRef()
			];
	}

	/*if (InColumnName == "Target")
	{
		return SNew(SBox)
			[
				PropertyModule.CreateSingleProperty(Objective, Objective->WorldTargetName, Params).ToSharedRef()
			];
	}*/

	if (InColumnName == "Target")
	{
		return SNew(SBox)
			[
				PropertyModule.CreateSingleProperty(Objective, Objective->WorldTargetName, Params).ToSharedRef()
			];
	}

	if (InColumnName == "TargetCount" && Objective->Type == EObjectiveType::Ot_Collect)
	{
		return SNew(SBox)
			[
				PropertyModule.CreateSingleProperty(Objective, "TargetCount", Params).ToSharedRef()
			];
	}
	else if (InColumnName == "TargetCount" && Objective->Type != EObjectiveType::Ot_Collect)
	{
		return SNew(STextBlock)
			.Text(FText::FromString(" - "));
	}

	/*if (InColumnName == "CollectCount" && Objective->Type == EObjectiveType::Ot_Collect)
	{
		return SNew(SBox)
			[
				PropertyModule.CreateSingleProperty(Objective, "CollectCount", Params).ToSharedRef()
			];
	}*/

	if (InColumnName == "Delete")
	{
		return SNew(SBox)
			[
				SNew(SButton)
				.OnPressed_Raw(this, &SObjectiveTableRow::RemoveObjective)
				[
					SNew(SBox)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Delete objective"))
					]
				]
			];
	}

	if (InColumnName == "Move")
	{
		return SNew(SBox)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
					.OnPressed_Raw(this, &SObjectiveTableRow::MoveUp)
					.IsEnabled(Quest->Objectives[0] != Objective)
					[
						SNew(SBox)
						[
							SNew(STextBlock)
							.Text(FText::FromString("Up"))
						]
					]
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
					.OnPressed_Raw(this, &SObjectiveTableRow::MoveDown)
					.IsEnabled(Quest->Objectives.Last() != Objective)
					[
						SNew(SBox)
						[
							SNew(STextBlock)
							.Text(FText::FromString("Down"))
						]
					]
				]
			];
	}
	
	return SNew(SBox)[SNew(STextBlock).Text(FText::FromString("Wrong field"))];
}

void SObjectiveTableRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)
{
	Objective = InArgs._Objective;
	Quest = InArgs._Quest;
	FSuperRowType::Construct(FSuperRowType::FArguments(), InOwnerTableView);
	ParentTable = &InOwnerTableView.Get();
}

void SObjectiveTableRow::RemoveObjective()
{
	Quest->Objectives.Remove(Objective);
	Quest->Modify();
	ParentTable->RequestListRefresh();
}

void SObjectiveTableRow::MoveUp()
{
	const int32 Index = Quest->Objectives.Find(Objective);
	if (Index == 0)
	{
		return;
	}
	
	Quest->Objectives.Swap(Index, Index - 1);
	Quest->Modify();
	ParentTable->RebuildList();
}

void SObjectiveTableRow::MoveDown()
{
	const int32 Index = Quest->Objectives.Find(Objective);
	if (Index == Quest->Objectives.Num() - 1)
	{
		return;
	}
	
	Quest->Objectives.Swap(Index, Index + 1);
	Quest->Modify();
	ParentTable->RebuildList();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

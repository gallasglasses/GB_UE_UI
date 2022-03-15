// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestEditorModeEdModeToolkit.h"
#include "QuestEditorModeEdMode.h"
#include "Engine/Selection.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Colors/SColorWheel.h"
#include "Widgets/Colors/SColorBlock.h"
#include "AppFramework/Public/Widgets/Colors/SColorPicker.h"
#include "EditorModeManager.h"
#include "Objective.h"
#include "Quest.h"
#include "QuestSystemCharacter.h"

#define LOCTEXT_NAMESPACE "FQuestEditorModeEdModeToolkit"

FQuestEditorModeEdModeToolkit::FQuestEditorModeEdModeToolkit()
{
}

void FQuestEditorModeEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	struct Locals
	{
		static bool IsWidgetEnabled()
		{
			return GEditor->GetSelectedActors()->Num() != 0;
		}

		static FReply OnMoveButtonClick(FVector InOffset)
		{
			USelection* SelectedActors = GEditor->GetSelectedActors();

			// Let editor know that we're about to do something that we want to undo/redo
			GEditor->BeginTransaction(LOCTEXT("MoveActorsTransactionName", "MoveActors"));

			// For each selected actor
			for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
			{
				if (AActor* LevelActor = Cast<AActor>(*Iter))
				{
					// Register actor in opened transaction (undo/redo)
					LevelActor->Modify();
					// Move actor to given location
					LevelActor->TeleportTo(LevelActor->GetActorLocation() + InOffset, FRotator(0, 0, 0));
				}
			}

			// We're done moving actors so close transaction
			GEditor->EndTransaction();

			return FReply::Handled();
		}

		static FReply OnSelectNPCButtonClick()
		{
			auto NPCEdMode = StaticCast<FQuestEditorModeEdMode*>(GLevelEditorModeTools().GetActiveMode(FQuestEditorModeEdMode::EM_QuestEditorModeEdModeId));
			NPCEdMode->bSelectedObjects = false;

			SelectedActors();

			return FReply::Handled();
		}
		
		static FReply OnSelectObjectsButtonClick()
		{
			auto NPCEdMode = StaticCast<FQuestEditorModeEdMode*>(GLevelEditorModeTools().GetActiveMode(FQuestEditorModeEdMode::EM_QuestEditorModeEdModeId));
			NPCEdMode->bSelectedObjects = true;

			SelectedActors();

			return FReply::Handled();
		}

		static void SelectedActors()
		{
			USelection* SelectedActors = GEditor->GetSelectedActors();
			TArray<AQuestSystemCharacter*> QuestNPCCharacters;

			// For each selected actor
			for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
			{
				if (AQuestSystemCharacter* LevelActor = Cast<AQuestSystemCharacter>(*Iter))
				{
					QuestNPCCharacters.AddUnique(LevelActor);
				}
			}
			GEditor->SelectNone(true, true);
			for (auto* QuestNPC : QuestNPCCharacters)
			{
				GEditor->SelectActor(QuestNPC, true, true);
			}
		}

		static FReply OnUnselectButtonClick()
		{
			GEditor->SelectNone(true, true);

			return FReply::Handled();
		}

		static TSharedRef<SWidget> MakeMoveButton(FText InLabel, const FVector InOffset)
		{
			return SNew(SButton)
				.Text(InLabel)
				.OnClicked_Static(&Locals::OnMoveButtonClick, InOffset);
		}

		static TSharedRef<SWidget> MakeSelectNPCButton(FText InLabel)
		{
			return SNew(SButton)
				.Text(InLabel)
				.OnClicked_Static(&Locals::OnSelectNPCButtonClick);
		}
		
		static TSharedRef<SWidget> MakeSelectObjectsButton(FText InLabel)
		{
			return SNew(SButton)
				.Text(InLabel)
				.OnClicked_Static(&Locals::OnSelectObjectsButtonClick);
		}
		
		static TSharedRef<SWidget> MakeUnselectButton(FText InLabel)
		{
			return SNew(SButton)
				.Text(InLabel)
				.OnClicked_Static(&Locals::OnUnselectButtonClick);
		}
	};

	const float Factor = 256.0f;

	SAssignNew(ToolkitWidget, SBorder)
		.HAlign(HAlign_Center)
		.Padding(25)
		.IsEnabled_Static(&Locals::IsWidgetEnabled)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Center)
			.Padding(20)
			[
				SNew(STextBlock)
				.AutoWrapText(true)
				.Text(LOCTEXT("HelperLabel1", "Select some actors and move them around using buttons below"))
			]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					Locals::MakeMoveButton(LOCTEXT("UpButtonLabel", "Up"), FVector(0, 0, Factor))
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						Locals::MakeMoveButton(LOCTEXT("LeftButtonLabel", "Left"), FVector(0, -Factor, 0))
					]
					+ SHorizontalBox::Slot()
						.AutoWidth()
						[
							Locals::MakeMoveButton(LOCTEXT("RightButtonLabel", "Right"), FVector(0, Factor, 0))
						]
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					Locals::MakeMoveButton(LOCTEXT("DownButtonLabel", "Down"), FVector(0, 0, -Factor))
				]
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Center)
				.Padding(20)
				[
					SNew(STextBlock)
					.AutoWrapText(true)
					.Text(LOCTEXT("HelperLabel2", "Shows all quest NPC on the map or objects of the selected NPC"))
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.Padding(15)
				.AutoHeight()
				[
					Locals::MakeSelectNPCButton(LOCTEXT("SelectNPCButtonLabel", "SelectNPC"))
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					SNew(STextBlock)
					.AutoWrapText(true)
					.Text(LOCTEXT("ColorQuestNPC", "Color Quest NPC"))
				]
			+SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.Padding(5)
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("Color", "Color"))
				]
					+ SHorizontalBox::Slot()
						.AutoWidth()
						.Padding(FMargin(10.f, 0.f))
					[
						SNew(SColorBlock)
						.Color(this, &FQuestEditorModeEdModeToolkit::GetColorNPCBoundingBox)
						.ShowBackgroundForAlpha(true)
						.IgnoreAlpha(true)
						.OnMouseButtonDown(this, &FQuestEditorModeEdModeToolkit::ColorBlockNPC_OnMouseButtonDown)
						.Size(FVector2D(100.0f, 14.0f))
					]
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.Padding(15)
				.AutoHeight()
				[
					Locals::MakeSelectObjectsButton(LOCTEXT("SelectObjectsButtonLabel", "SelectObjects"))
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					SNew(STextBlock)
					.AutoWrapText(true)
					.Text(LOCTEXT("ColorQuestObjects", "Color Quest Objects"))
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.Padding(5)
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("Color", "Color"))
				]
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(FMargin(10.f, 0.f))
				[
					SNew(SColorBlock)
					.Color(this, &FQuestEditorModeEdModeToolkit::GetColorObjectsBoundingBox)
				.ShowBackgroundForAlpha(true)
				.IgnoreAlpha(true)
				.OnMouseButtonDown(this, &FQuestEditorModeEdModeToolkit::ColorBlockObjects_OnMouseButtonDown)
				.Size(FVector2D(100.0f, 14.0f))
				]
			]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.Padding(20)
				.AutoHeight()
				[
					Locals::MakeUnselectButton(LOCTEXT("UnselectAllButtonLabel", "UnselectAll"))
				]
		];
		
	FModeToolkit::Init(InitToolkitHost);
}

FName FQuestEditorModeEdModeToolkit::GetToolkitFName() const
{
	return FName("QuestEditorModeEdMode");
}

FText FQuestEditorModeEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("QuestEditorModeEdModeToolkit", "DisplayName", "QuestEditorModeEdMode Tool");
}

class FEdMode* FQuestEditorModeEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FQuestEditorModeEdMode::EM_QuestEditorModeEdModeId);
}

FLinearColor FQuestEditorModeEdModeToolkit::GetColorNPCBoundingBox() const
{
	auto NPCEdMode = StaticCast<FQuestEditorModeEdMode*>(GetEditorMode());
	return NPCEdMode->ColorNPCBoundingBox;
}

FLinearColor FQuestEditorModeEdModeToolkit::GetColorObjectsBoundingBox() const
{
	auto ObjectsEdMode = StaticCast<FQuestEditorModeEdMode*>(GetEditorMode());
	return ObjectsEdMode->ColorObjectsBoundingBox; //.ReinterpretAsLinear()
}

void FQuestEditorModeEdModeToolkit::SetColorNPCBoundingBox(FLinearColor NewColor)
{
	auto NPCEdMode = StaticCast<FQuestEditorModeEdMode*>(GetEditorMode());
	NPCEdMode->ColorNPCBoundingBox = NewColor;
	//GetEditorMode()->BaseBoxColor = NewColor.ToFColor(true);
}

void FQuestEditorModeEdModeToolkit::SetColorObjectsBoundingBox(FLinearColor NewColor)
{
	auto ObjectsEdMode = StaticCast<FQuestEditorModeEdMode*>(GetEditorMode());
	ObjectsEdMode->ColorObjectsBoundingBox = NewColor;
}

FReply FQuestEditorModeEdModeToolkit::ColorBlockNPC_OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() != EKeys::LeftMouseButton)
	{
		return FReply::Unhandled();
	}

	//#include "UserInterface/PropertyEditor/SPropertyEditorColor.h"
	//CreateColorPickerWindow(PropertyEditor.ToSharedRef(), bUseAlpha, bRefreshOnlyOnOk);

	FLinearColor InitialColor = GetColorNPCBoundingBox();

	FColorPickerArgs PickerArgs;
	PickerArgs.bOnlyRefreshOnMouseUp = true;
	//PickerArgs.ParentWidget = AsShared();
	PickerArgs.bUseAlpha = true; //const bool bUseAlpha = !(Property->GetOwnerClass() && (Property->GetOwnerClass()->IsChildOf(ULightComponent::StaticClass()) || bRefreshOnlyOnOk));
	PickerArgs.bOnlyRefreshOnOk = true; //bool bRefreshOnlyOnOk = Property->GetOwnerClass() && Property->GetOwnerClass()->IsChildOf(UMaterialExpressionConstant3Vector::StaticClass());
	PickerArgs.DisplayGamma = TAttribute<float>::Create(TAttribute<float>::FGetter::CreateUObject(GEngine, &UEngine::GetDisplayGamma));
	PickerArgs.OnColorCommitted = FOnLinearColorValueChanged::CreateSP(this, &FQuestEditorModeEdModeToolkit::SetColorNPCBoundingBox);
	//PickerArgs.OnColorPickerCancelled = FOnColorPickerCancelled::CreateSP(this, &SPropertyEditorColor::OnColorPickerCancelled);
	PickerArgs.InitialColorOverride = InitialColor;

	OpenColorPicker(PickerArgs);

	return FReply::Handled();
}

FReply FQuestEditorModeEdModeToolkit::ColorBlockObjects_OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() != EKeys::LeftMouseButton)
	{
		return FReply::Unhandled();
	}

	FLinearColor InitialColor = GetColorObjectsBoundingBox();

	FColorPickerArgs PickerArgs;
	PickerArgs.bOnlyRefreshOnMouseUp = true;
	
	PickerArgs.bUseAlpha = true; 
	PickerArgs.bOnlyRefreshOnOk = true;
	PickerArgs.DisplayGamma = TAttribute<float>::Create(TAttribute<float>::FGetter::CreateUObject(GEngine, &UEngine::GetDisplayGamma));
	PickerArgs.OnColorCommitted = FOnLinearColorValueChanged::CreateSP(this, &FQuestEditorModeEdModeToolkit::SetColorObjectsBoundingBox);
	PickerArgs.InitialColorOverride = InitialColor;

	OpenColorPicker(PickerArgs);

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE

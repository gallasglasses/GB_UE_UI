// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestEditorModeEdMode.h"
#include "QuestEditorModeEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"
#include "Engine/Selection.h"
#include "Objective.h"
#include "Quest.h"
#include "QuestSystemCharacter.h"
#include "CollectableObject.h"
#include "Kismet/GameplayStatics.h"

const FEditorModeID FQuestEditorModeEdMode::EM_QuestEditorModeEdModeId = TEXT("EM_QuestEditorModeEdMode");

FQuestEditorModeEdMode::FQuestEditorModeEdMode()
{

}

FQuestEditorModeEdMode::~FQuestEditorModeEdMode()
{

}

void FQuestEditorModeEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FQuestEditorModeEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}

	UpdateSelectedActors();
}

void FQuestEditorModeEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

void FQuestEditorModeEdMode::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	for (AActor* Actor : SelectedActors)
	{
		DrawWireBox(PDI, Actor->GetComponentsBoundingBox(true), ColorNPCBoundingBox, 1);
	}

	for (AActor* Objects : SelectedObjects)
	{
		DrawWireBox(PDI, Objects->GetComponentsBoundingBox(true), ColorObjectsBoundingBox, 1);
	}

	FEdMode::Render(View, Viewport, PDI);
}

void FQuestEditorModeEdMode::ActorSelectionChangeNotify()
{
	FEdMode::ActorSelectionChangeNotify();

	UpdateSelectedActors();
}

bool FQuestEditorModeEdMode::UsesToolkits() const
{
	return true;
}

void FQuestEditorModeEdMode::DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas)
{
	FEdMode::DrawHUD(ViewportClient, Viewport, View, Canvas);

	if (Canvas == nullptr)
	{
		return;
	}

	for (AActor* Actor : SelectedActors)
	{
		const FBox ActorBounds = Actor->GetComponentsBoundingBox(true);

		const FVector DrawLoc = ActorBounds.GetCenter() + FVector(0.f, 0.f, ActorBounds.GetExtent().Z);

		FVector2D DrawPixel;
		View->WorldToPixel(DrawLoc, DrawPixel);

		DrawPixel /= ViewportClient->GetDPIScale();

		const FText DrawText = FText::FromString(Actor->GetName());

		Canvas->DrawShadowedText(DrawPixel.X, DrawPixel.Y, DrawText, GEngine->GetSmallFont(), ColorNPCBoundingBox);
	}

	for (AActor* Objects : SelectedObjects)
	{
		const FBox ActorBounds = Objects->GetComponentsBoundingBox(true);

		const FVector DrawLoc = ActorBounds.GetCenter() + FVector(0.f, 0.f, ActorBounds.GetExtent().Z);

		FVector2D DrawPixel;
		View->WorldToPixel(DrawLoc, DrawPixel);

		DrawPixel /= ViewportClient->GetDPIScale();

		const FText DrawText = FText::FromString(Objects->GetName());

		Canvas->DrawShadowedText(DrawPixel.X, DrawPixel.Y, DrawText, GEngine->GetSmallFont(), ColorObjectsBoundingBox);
	}
}

void FQuestEditorModeEdMode::UpdateSelectedActors()
{
	SelectedActors.Empty();
	SelectedObjects.Empty();

	USelection* Selection = GEditor->GetSelectedActors();
	for (FSelectionIterator Iter(*Selection); Iter; ++Iter)
	{
		if (AActor* SelectedActor = Cast<AActor>(*Iter))
		{
			SelectedActors.AddUnique(SelectedActor);
		}
	}

	if (bSelectedObjects)
	{
		TArray<UObjective*> Objects;
		for (auto Actor : SelectedActors)
		{
			TArray<AActor*> AttachedActors;
			Actor->GetAttachedActors(AttachedActors);
			for (auto AttachedActor : AttachedActors)
			{
				if (AQuest* Quest = Cast<AQuest>(AttachedActor))
				{
					Objects.Append(Quest->GetObjectives());
				}
			}
		}

		for (UObjective* Object : Objects)
		{
			if (UInteractionObjective* InteractionObject = Cast<UInteractionObjective>(Object))
			{
				SelectedObjects.Add(InteractionObject->Target);
			}
			if (ULocationObjective* LocationObject = Cast<ULocationObjective>(Object))
			{
				SelectedObjects.Add(LocationObject->Marker);
			}
			if (UCollectionObjective* CollectionObject = Cast<UCollectionObjective>(Object))
			{
				auto CollectionObjectTag = CollectionObject->TargetTag;

				TArray<AActor*> IntendedTarget;
				UGameplayStatics::GetAllActorsWithTag(GetWorld(), CollectionObjectTag, IntendedTarget);

				for (int32 i = 0; i < IntendedTarget.Num(); i++)
				{
					if (ICollectableObject* InteractTarget = Cast<ICollectableObject>(IntendedTarget[i]))
					{
						SelectedObjects.Add(IntendedTarget[i]);
					}
				}

			}
		}
	}
}





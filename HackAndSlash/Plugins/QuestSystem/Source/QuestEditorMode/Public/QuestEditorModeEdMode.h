// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"

class UObjective;
class AQuestSystemCharacter;

class FQuestEditorModeEdMode : public FEdMode
{
public:
	const static FEditorModeID EM_QuestEditorModeEdModeId;
public:
	FQuestEditorModeEdMode();
	virtual ~FQuestEditorModeEdMode();

	// FEdMode interface
	virtual void Enter() override;
	virtual void Exit() override;
	//virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;
	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	virtual void ActorSelectionChangeNotify() override;
	bool UsesToolkits() const override;
	// End of FEdMode interface

	virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;

	FLinearColor ColorObjectsBoundingBox = FLinearColor::Gray;
	FLinearColor ColorNPCBoundingBox = FLinearColor::Yellow;

	bool bSelectedObjects = false;

protected:
	
	TArray<AActor*> SelectedActors;
	TArray<AActor*> SelectedObjects;

	void UpdateSelectedActors();
};
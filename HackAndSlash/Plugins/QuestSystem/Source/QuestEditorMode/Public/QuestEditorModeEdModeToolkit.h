// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/BaseToolkit.h"

class UObjective;
class AQuestSystemCharacter;

class FQuestEditorModeEdModeToolkit : public FModeToolkit
{
public:

	FQuestEditorModeEdModeToolkit();
	
	/** FModeToolkit interface */
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual class FEdMode* GetEditorMode() const override;
	virtual TSharedPtr<class SWidget> GetInlineContent() const override { return ToolkitWidget; }

private:

	TSharedPtr<SWidget> ToolkitWidget;

	FLinearColor GetColorNPCBoundingBox() const;
	FLinearColor GetColorObjectsBoundingBox() const;

	void SetColorNPCBoundingBox(FLinearColor NewColor);
	void SetColorObjectsBoundingBox(FLinearColor NewColor);

	FReply ColorBlockNPC_OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);
	FReply ColorBlockObjects_OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);
};

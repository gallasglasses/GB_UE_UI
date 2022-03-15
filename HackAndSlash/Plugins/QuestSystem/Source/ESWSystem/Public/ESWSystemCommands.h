// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ESWSystemStyle.h"

class FESWSystemCommands : public TCommands<FESWSystemCommands>
{
public:

	FESWSystemCommands()
		: TCommands<FESWSystemCommands>(TEXT("ESWSystem"), NSLOCTEXT("Contexts", "ESWSystem", "Edit Test Plugin"), NAME_None, FESWSystemStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};
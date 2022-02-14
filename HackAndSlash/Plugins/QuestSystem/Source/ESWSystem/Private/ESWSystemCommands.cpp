// Copyright Epic Games, Inc. All Rights Reserved.

#include "ESWSystemCommands.h"

#define LOCTEXT_NAMESPACE "FESWSystemModule"

void FESWSystemCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "ESWSystem", "Bring up ESWSystem window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE

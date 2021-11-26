// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HackAndSlash : ModuleRules
{
	public HackAndSlash(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PrivateIncludePaths.AddRange(new string[] 
		{ 
			"HackAndSlash/Public/Player",
			"HackAndSlash/Public/Components",
            "HackAndSlash/Public/Dev",
            "HackAndSlash/Public/UI",
            "HackAndSlash/Public/Animations",
			"HackAndSlash/Public/Menu",
            "HackAndSlash/Public/Menu/UI"
        });
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

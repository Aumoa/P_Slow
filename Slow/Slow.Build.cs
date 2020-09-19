// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Slow : ModuleRules
{
	public Slow(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseRTTI = true;
	
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"NavigationSystem",
			"AIModule",
			"UMG",
			"Slate",
			"SlateCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}

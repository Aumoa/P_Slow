// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Slow : ModuleRules
{
	public Slow(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.NoSharedPCHs;
		bUseRTTI = true;
		PrivatePCHHeaderFile = "Slow.h";
		CppStandard = CppStandardVersion.Cpp17;
	
		PublicDependencyModuleNames.AddRange(new string[] {
			/* EngineCore */
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"NavigationSystem",
			"AIModule",
			"UMG",
			"Slate",
			"SlateCore",

			/* Plugins */
			"ApexDestruction"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}

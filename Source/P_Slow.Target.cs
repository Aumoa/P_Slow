// Copyright 2020. Team slow, All right reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class P_SlowTarget : TargetRules
{
	public P_SlowTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "P_Slow" } );
	}
}

// Copyright 2020 Team slow. All right reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class P_SlowEditorTarget : TargetRules
{
	public P_SlowEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "P_Slow" } );
	}
}

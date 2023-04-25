// Shoot Them Up 4.26.All Rights reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class ShootThemUp426EditorTarget : TargetRules
{
	public ShootThemUp426EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShootThemUp426" } );
	}
}

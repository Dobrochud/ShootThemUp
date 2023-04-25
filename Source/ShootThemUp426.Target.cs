// Shoot Them Up 4.26.All Rights reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class ShootThemUp426Target : TargetRules
{
	public ShootThemUp426Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShootThemUp426" } );
	}
}

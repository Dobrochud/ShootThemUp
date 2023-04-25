// Shoot Them Up 4.26.All Rights reserved

using UnrealBuildTool;

public class ShootThemUp426 : ModuleRules
{
	public ShootThemUp426(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"Niagara",
			"GameplayTasks",
			"NavigationSystem",
			"PhysicsCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		PublicIncludePaths.AddRange(new string[] 
		{
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

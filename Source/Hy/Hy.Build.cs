// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Hy : ModuleRules
{
	public Hy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Sockets", "Networking" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PrivateIncludePaths.AddRange(new string[]
        {
            "Hy/",
            "Hy/Public/Character/",
            "Hy/Public/Game/",
            "Hy/Public/Manager/",
            "Hy/Public/Network/",
            "Hy/Public/Animation",
            "Hy/Public/Actor",
        });
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}

// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class Hy : ModuleRules
{
	public Hy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
            "EnhancedInput", "Sockets", "Networking", "AnimGraphRuntime", "UMG", "AIModule", "GameplayTags",
            "NavigationSystem", "Niagara",
            "MotionWarping", "AnimationLocomotionLibraryRuntime"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { "ProtobufCore" });

        PrivateIncludePaths.AddRange(new string[]
        {
            "Hy/",
            "Hy/Public/Character/",
            "Hy/Public/Game/",
            "Hy/Public/Manager/",
            "Hy/Public/Network/",
            "Hy/Public/Network/Protocol",
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

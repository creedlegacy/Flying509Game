// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Flying509Game : ModuleRules
{
	public Flying509Game(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}

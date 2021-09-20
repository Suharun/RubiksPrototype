// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LJMUFPS425 : ModuleRules
{
	public LJMUFPS425(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}

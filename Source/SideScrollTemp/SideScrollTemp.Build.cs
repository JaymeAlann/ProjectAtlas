// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SideScrollTemp : ModuleRules
{
	public SideScrollTemp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });
	}
}

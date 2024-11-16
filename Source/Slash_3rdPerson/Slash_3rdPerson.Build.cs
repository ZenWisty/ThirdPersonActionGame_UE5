// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Slash_3rdPerson : ModuleRules
{
	public Slash_3rdPerson(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}

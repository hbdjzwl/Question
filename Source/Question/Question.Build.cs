// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Question : ModuleRules
{
	public Question(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore"});
	}
}

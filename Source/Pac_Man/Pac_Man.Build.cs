// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Pac_Man : ModuleRules
{
	public Pac_Man(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}

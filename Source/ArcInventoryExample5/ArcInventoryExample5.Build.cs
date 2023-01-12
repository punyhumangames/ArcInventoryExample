// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.

using UnrealBuildTool;

public class ArcInventoryExample5 : ModuleRules
{
	public ArcInventoryExample5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"GameplayAbilities", 
			"ArcInventory", 
			"GameplayTags",
			"EnhancedInput"
		});
	}
}

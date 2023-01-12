// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.

using UnrealBuildTool;

public class ArcInventoryEnhancedInput : ModuleRules
{
	public ArcInventoryEnhancedInput(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;		
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"ArcInventory",
				"EnhancedInput",
				"GameplayAbilities",
			});
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			});		

	}
}

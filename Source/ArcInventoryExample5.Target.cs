// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.

using UnrealBuildTool;
using System.Collections.Generic;

public class ArcInventoryExample5Target : TargetRules
{
	public ArcInventoryExample5Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("ArcInventoryExample5");
	}
}

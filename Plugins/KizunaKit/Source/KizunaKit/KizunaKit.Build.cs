// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class KizunaKit : ModuleRules
{
	public KizunaKit(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"InputCore",
				"Engine",
				"InputDevice",
				"ApplicationCore"
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
		);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);
		
		// BNUsioのDLLをパッケージ時にコピーする
		var DllExplicitPath = Path.Combine(PluginDirectory, "./Library/bnusio.dll");
		PublicDelayLoadDLLs.Add(DllExplicitPath);
		RuntimeDependencies.Add(DllExplicitPath);
	}
}
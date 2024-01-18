// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class hakoniwa_plugin : ModuleRules
{
	public hakoniwa_plugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
        string ThirdPartyCorePath = Path.Combine(ModuleDirectory, "../../../hakoniwa-core-cpp-client");
        string ThirdPartyPduPath = Path.Combine(ModuleDirectory, "../../../hakoniwa-ros2pdu");
        string LibCorePath = Path.Combine(ThirdPartyCorePath, "cmake-build/core/src");
        string DyLibCorePath = Path.Combine(ThirdPartyCorePath, "cmake-build/src/assets");
        string IncludeCorePath = Path.Combine(ThirdPartyCorePath, "src/include");
        string IncludePduPath = Path.Combine(ThirdPartyPduPath, "pdu/types");
        
        // ヘッダーファイルへのパスを追加
        PublicIncludePaths.AddRange(new string[] { IncludeCorePath });
        PublicIncludePaths.AddRange(new string[] { IncludePduPath });

        // 静的ライブラリへのリンクを追加
        PublicAdditionalLibraries.Add(Path.Combine(LibCorePath, "libhako.a"));

        // 動的ライブラリへのリンクを追加
        PublicDelayLoadDLLs.Add(Path.Combine(DyLibCorePath, "libassets.dylib"));
        RuntimeDependencies.Add(Path.Combine(DyLibCorePath, "libassets.dylib"));		
	}
}

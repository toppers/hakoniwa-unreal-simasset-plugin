// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class plugin : ModuleRules
{
	public plugin(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
        
        PrivateDependencyModuleNames.AddRange(new string[] {  });
        
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
        
        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");
        
        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
        // ThirdParty/AssetsLibrary ディレクトリへのパス
        string ThirdPartyPath = Path.Combine(ModuleDirectory, "../../../hakoniwa-core-cpp-client");
        string LibCorePath = Path.Combine(ThirdPartyPath, "cmake-build/core/src");
        string DyLibCorePath = Path.Combine(ThirdPartyPath, "cmake-build/src/assets");
        string IncludePath = Path.Combine(ThirdPartyPath, "src/include");
        
        // ヘッダーファイルへのパスを追加
        PublicIncludePaths.AddRange(new string[] { IncludePath });

        // 静的ライブラリへのリンクを追加
        PublicAdditionalLibraries.Add(Path.Combine(LibCorePath, "libhako.a"));

        // 動的ライブラリへのリンクを追加
        PublicDelayLoadDLLs.Add(Path.Combine(DyLibCorePath, "libassets.dylib"));
        RuntimeDependencies.Add(Path.Combine(DyLibCorePath, "libassets.dylib"));
        
    }
}

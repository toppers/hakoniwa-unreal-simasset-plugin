// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"

#include "Modules/ModuleManager.h"


/**
 * 
 */
class PLUGIN_API HakoAsset: public IModuleInterface
{
public:
    // モジュールの開始時に呼ばれる関数
    virtual void StartupModule() override;

    // モジュールの終了時に呼ばれる関数
    virtual void ShutdownModule() override;
	void InitializeAsset();
};

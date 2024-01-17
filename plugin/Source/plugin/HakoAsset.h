// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"

#include "Modules/ModuleManager.h"
#include "HakoAssetTask.h"
#include "hako_asset.h"

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
	bool InitializeAsset();
	void FinalizeAsset();
    uint64 GetHakoSimTimeUsec();
    bool NotifyAssetSimTimeUsec(uint64 asset_simtime_usec);
    // PDU読み込み関数
    int ReadPdu(const FString& RoboName, HakoPduChannelIdType Channel, char* Buffer, int pdu_size);

    // PDU書き込み関数
    int WritePdu(const FString& RoboName, HakoPduChannelIdType Channel, const char* Buffer, int pdu_size);

private:
    HakoAssetTask* RunnableTask = nullptr;
	FRunnableThread* RunnableThread = nullptr;
};

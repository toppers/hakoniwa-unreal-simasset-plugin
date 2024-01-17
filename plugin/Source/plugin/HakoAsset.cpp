// Fill out your copyright notice in the Description page of Project Settings.


#include "HakoAsset.h"
#include "Interfaces/IPluginManager.h"
#include "Logging/LogMacros.h"
#include "Misc/OutputDevice.h"

void HakoAsset::StartupModule()
{
    UE_LOG(LogTemp, Log, TEXT("HakoAsset Started"));
}

void HakoAsset::FinalizeAsset()
{
    UE_LOG(LogTemp, Warning, TEXT("FinalizeAsset() Enter"));
    if (RunnableTask != nullptr)
    {
        // スレッドの停止を要求
        RunnableTask->Stop();

        // スレッドが完全に終了するまで待機
        RunnableThread->WaitForCompletion();

        // リソースの解放
        delete RunnableTask;
        RunnableTask = nullptr;

        delete RunnableThread;
        RunnableThread = nullptr;
    }

    UE_LOG(LogTemp, Log, TEXT("HakoAsset FinalizeAsset() Exit"));
}
void HakoAsset::ShutdownModule()
{
    FinalizeAsset();
}

bool HakoAsset::InitializeAsset()
{
    UE_LOG(LogTemp, Log, TEXT("InitializeAsset() Enter"));
    RunnableTask = new HakoAssetTask();
    RunnableThread = FRunnableThread::Create(RunnableTask, TEXT("HakoAssetTaskThread"));
    if (RunnableThread == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("InitializeAsset() error Exit: can not create thread"));
        return false;
    }
    UE_LOG(LogTemp, Log, TEXT("InitializeAsset() Exit"));
    return true;
}
uint64 HakoAsset::GetHakoSimTimeUsec()
{
    if (RunnableTask != nullptr)
    {
        return RunnableTask->GetHakoSimTimeUsec();
    }
    return 0;
}
bool HakoAsset::NotifyAssetSimTimeUsec(uint64 asset_simtime_usec)
{
    if (RunnableTask != nullptr)
    {
        return RunnableTask->NotifyAssetSimTimeUsec(asset_simtime_usec);
    }
    return false;
}

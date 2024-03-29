// Fill out your copyright notice in the Description page of Project Settings.


#include "HakoAssetModule.h"
#include "Interfaces/IPluginManager.h"
#include "Logging/LogMacros.h"
#include "Misc/OutputDevice.h"

void HakoAssetModule::StartupModule()
{
    UE_LOG(LogTemp, Log, TEXT("HakoAssetModule Started"));
}

void HakoAssetModule::FinalizeAsset()
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

    UE_LOG(LogTemp, Log, TEXT("HakoAssetModule FinalizeAsset() Exit"));
}
void HakoAssetModule::ShutdownModule()
{
    FinalizeAsset();
}

bool HakoAssetModule::InitializeAsset()
{
    UE_LOG(LogTemp, Log, TEXT("InitializeAsset() Enter"));
    AssetSimTimeUsec = 0;
    RunnableTask = new HakoAssetTask();
    RunnableThread = FRunnableThread::Create(RunnableTask, TEXT("HakoAssetTaskThread"));
    if (RunnableThread == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("InitializeAsset() error Exit: can not create thread"));
        return false;
    }
    UE_LOG(LogTemp, Log, TEXT("InitializeAsset() Exit"));
    return true;
}
uint64 HakoAssetModule::GetHakoSimTimeUsec()
{
    if (RunnableTask != nullptr)
    {
        return RunnableTask->GetHakoSimTimeUsec();
    }
    return 0;
}
bool HakoAssetModule::NotifyAssetSimTimeUsec(uint64 delta_time_usec)
{
    if (RunnableTask != nullptr)
    {
        if (AssetSimTimeUsec < GetHakoSimTimeUsec()) {
            if (RunnableTask->NotifyAssetSimTimeUsec(AssetSimTimeUsec + delta_time_usec)) {
                AssetSimTimeUsec += delta_time_usec;
                return true;
            }
            else {
                return false;
            }
        }
        else {
            //UE_LOG(LogTemp, Log, TEXT("AssetSimTimeUsec: %llu"), AssetSimTimeUsec);
            //UE_LOG(LogTemp, Log, TEXT("GetHakoSimTimeUsec: %llu"), GetHakoSimTimeUsec());
            return false;
        }
    }
    return false;
}


int HakoAssetModule::ReadPdu(const FString& RoboName, HakoPduChannelIdType Channel, char* Buffer, int pdu_size)
{
    // BufferをANSI文字列に変換
    int Result = hako_asset_pdu_read(TCHAR_TO_ANSI(*RoboName), Channel, Buffer, pdu_size);
    
    return Result;
}

int HakoAssetModule::WritePdu(const FString& RoboName, HakoPduChannelIdType Channel, const char* Buffer, int pdu_size)
{
    // TArray<uint8>をANSI文字列に変換
    return hako_asset_pdu_write(TCHAR_TO_ANSI(*RoboName), Channel, Buffer, pdu_size);
}

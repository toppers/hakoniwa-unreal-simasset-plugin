// Fill out your copyright notice in the Description page of Project Settings.


#include "HakoAsset.h"
#include "Interfaces/IPluginManager.h"
#include "Logging/LogMacros.h"
#include "Misc/OutputDevice.h"
#include "HakoAssetTask.h"

void HakoAsset::StartupModule()
{
    UE_LOG(LogTemp, Log, TEXT("HakoAsset Started"));
}

void HakoAsset::ShutdownModule()
{
    UE_LOG(LogTemp, Log, TEXT("HakoAsset Shutdown"));
}

bool HakoAsset::InitializeAsset()
{
    UE_LOG(LogTemp, Log, TEXT("InitializeAsset() Enter"));
    RunnableThread = FRunnableThread::Create(new HakoAssetTask(), TEXT("HakoAssetTaskThread"));
    if (RunnableThread == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("InitializeAsset() error Exit: can not create thread"));
        return false;
    }
    UE_LOG(LogTemp, Log, TEXT("InitializeAsset() Exit"));
    return true;
}

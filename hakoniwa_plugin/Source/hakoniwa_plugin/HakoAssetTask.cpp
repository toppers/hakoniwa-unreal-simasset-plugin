// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/Paths.h"
#include "Containers/StringConv.h"
#include "HakoAssetTask.h"
#include "hako_asset.h"
#include <filesystem>
#include <thread>

static int my_on_initialize(hako_asset_context_t* context);
static int my_on_reset(hako_asset_context_t* context);
static int my_on_manual_timing_control(hako_asset_context_t* context);
static hako_asset_callbacks_t my_callback = {
    .on_initialize = my_on_initialize,
    .on_manual_timing_control = my_on_manual_timing_control,
    .on_simulation_step = NULL,
    .on_reset = my_on_reset
};
FCriticalSection Mutex;

static std::atomic<uint64>  req_asset_simtime_usec = 0;
static std::atomic<uint64>  current_simtime_usec = 0;

bool HakoAssetTask::Init()
{
    req_asset_simtime_usec = 0;
    current_simtime_usec = 0;
    //TODO absolute path to config settings.
    FString ProjectRoot = FPaths::ProjectDir();
    // "/custom.json" を連結
    FString FullPath = ProjectRoot + "custom.json";

    // FString を std::string に変換
    std::string StdString = TCHAR_TO_UTF8(*FullPath);

    // std::string を const char* に変換
    const char* CharPath = StdString.c_str();

    //UE_LOG(LogTemp, Warning, TEXT("custom.json path: %s"), CharPath);
    UE_LOG(LogTemp, Log, TEXT("hako_asset_register() success."));
    int ret = hako_asset_register("UnrealHakoAsset", CharPath, &my_callback, HAKO_ASSET_DELTAT_TIME_USEC);
    if (ret != 0) {
        UE_LOG(LogTemp, Error, TEXT("hako_asset_register() error: ret = %d"), ret);
        return false;
    }
    UE_LOG(LogTemp, Log, TEXT("hako_asset_register() success."));

    return true;
}
uint64 HakoAssetTask::GetHakoSimTimeUsec()
{
    return hako_asset_simulation_time();
}
uint64 HakoAssetTask::GetAssetSimTimeUsec()
{
    return current_simtime_usec;
}

bool HakoAssetTask::NotifyAssetSimTimeUsec(uint64 asset_simtime_usec)
{
    if (req_asset_simtime_usec == current_simtime_usec) {
        req_asset_simtime_usec = asset_simtime_usec;
        return true;
    }
    else {
        //doing..
        return false;
    }
}

uint32 HakoAssetTask::Run()
{
    int ret = hako_asset_start();
    if (ret != 0) {
        UE_LOG(LogTemp, Error, TEXT("hako_asset_start() error: ret = %d"), ret);
        return ret;
    }
    UE_LOG(LogTemp, Log, TEXT("hako_asset_start() success."));

    return 0;
}
static std::atomic<bool> background_thread_stop = false;
static std::atomic<bool> background_thread_doing = false;
void HakoAssetTask::Stop()
{
    UE_LOG(LogTemp, Warning, TEXT("HakoAssetTask: Stop() start."));
    background_thread_stop = true;
    while (background_thread_doing) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    UE_LOG(LogTemp, Warning, TEXT("HakoAssetTask: Stop() exit."));
    background_thread_stop = false;
    return;
}


static int my_on_initialize(hako_asset_context_t* context)
{
    UE_LOG(LogTemp, Log, TEXT("my_on_initialize() success."));
    req_asset_simtime_usec = 0;
    current_simtime_usec = 0;
    return 0;
}
static int my_on_reset(hako_asset_context_t* context)
{
    UE_LOG(LogTemp, Log, TEXT("my_on_reset() success."));
    req_asset_simtime_usec = 0;
    current_simtime_usec = 0;
    return 0;
}

static int my_on_manual_timing_control(hako_asset_context_t* context)
{
    background_thread_doing = true;
    UE_LOG(LogTemp, Warning, TEXT("my_on_manual_timing_control() enter"));
    int result = 0;
    result = hako_asset_usleep(1);
    while (result == 0) {
        //UE_LOG(LogTemp, Warning, TEXT("world_simtime_usec: %lld"), hako_asset_simulation_time());
        //UE_LOG(LogTemp, Warning, TEXT("current_simtime_usec: %lld"), current_simtime_usec);
        if (req_asset_simtime_usec > current_simtime_usec) {
            uint64 sleep_time_usec = req_asset_simtime_usec - current_simtime_usec;
            result = hako_asset_usleep(sleep_time_usec);
            current_simtime_usec += sleep_time_usec;
        }
        else {
            //nothing to do
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        if (background_thread_stop) {
            break;
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("my_on_manual_timing_control() exit"));
    background_thread_doing = false;
    return 0;
}

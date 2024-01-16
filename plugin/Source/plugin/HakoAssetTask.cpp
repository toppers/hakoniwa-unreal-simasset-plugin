// Fill out your copyright notice in the Description page of Project Settings.


#include "HakoAssetTask.h"
#include "hako_asset.h"
#include <filesystem>

static int my_on_initialize(hako_asset_context_t* context);
static int my_on_reset(hako_asset_context_t* context);
static int my_on_manual_timing_control(hako_asset_context_t* context);
static hako_asset_callbacks_t my_callback = {
    .on_initialize = my_on_initialize,
    .on_manual_timing_control = my_on_manual_timing_control,
    .on_simulation_step = NULL,
    .on_reset = my_on_reset
};
bool HakoAssetTask::Init()
{
    //TODO absolute path to config settings.
    const char* path = "/Users/tmori/project/oss/hakoniwa-unreal-simasset-plugin/plugin/custom.json";
    int ret = hako_asset_register("UnrealHakoAsset", path, &my_callback, 1000);
    if (ret != 0) {
        UE_LOG(LogTemp, Error, TEXT("hako_asset_register() error: ret = %d"), ret);
        return true;
    }
    UE_LOG(LogTemp, Log, TEXT("hako_asset_register() success."));

    return true;
}

uint32 HakoAssetTask::Run()
{
    return 0;
}

void HakoAssetTask::Stop()
{
    return;
}


static int my_on_initialize(hako_asset_context_t* context)
{
    printf("INFO: my_on_initialize enter\n");
    printf("INFO: sleep 1sec\n");
    usleep(1000*1000);
    printf("INFO: my_on_initialize exit\n");
    return 0;
}
static int my_on_reset(hako_asset_context_t* context)
{
    printf("INFO: my_on_reset enter\n");
    printf("INFO: sleep 1sec\n");
    usleep(1000*1000);
    printf("INFO: my_on_reset exit\n");
    return 0;
}

static int my_on_manual_timing_control(hako_asset_context_t* context)
{
    UE_LOG(LogTemp, Warning, TEXT("my_on_manual_timing_control() enter"));
    int result = 1;
    while (result == 0) {
        printf("INFO: sleep 1sec: %llu\n", hako_asset_simulation_time());
        result = hako_asset_usleep(1000);
        usleep(1000*1000);
    }
    UE_LOG(LogTemp, Warning, TEXT("my_on_manual_timing_control() exit"));
    return 0;
}

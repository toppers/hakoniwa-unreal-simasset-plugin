// Fill out your copyright notice in the Description page of Project Settings.


#include "HakoAsset.h"
#include "Interfaces/IPluginManager.h"
#include "Logging/LogMacros.h"
#include "Misc/OutputDevice.h"
#include "hako_asset.h"
#include <filesystem>

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
static int my_on_simulation_step(hako_asset_context_t* context)
{
    printf("INFO: on_simulation_step enter: %llu\n", hako_asset_simulation_time());
    printf("INFO: sleep 1sec\n");
    usleep(1000*1000);
    printf("INFO: on_simulation_step exit\n");
    return 0;
}
static int my_on_manual_timing_control(hako_asset_context_t* context)
{
    printf("INFO: on_manual_timing_control enter\n");
    int result = 0;
    while (result == 0) {
        printf("INFO: sleep 1sec: %llu\n", hako_asset_simulation_time());
        result = hako_asset_usleep(1000);
        usleep(1000*1000);
    }
    printf("INFO: on_manual_timing_control exit\n");
    return 0;
}

static hako_asset_callbacks_t my_callback = {
    .on_initialize = my_on_initialize,
    .on_manual_timing_control = NULL,
    .on_simulation_step = my_on_simulation_step,
    .on_reset = my_on_reset
};

void HakoAsset::StartupModule()
{
    UE_LOG(LogTemp, Warning, TEXT("HakoAsset Started"));
}

void HakoAsset::ShutdownModule()
{
    UE_LOG(LogTemp, Warning, TEXT("HakoAsset Shutdown"));
}

void HakoAsset::InitializeAsset()
{
    UE_LOG(LogTemp, Warning, TEXT("InitializeAsset() Enter"));
    //TODO absolute path to config settings.
    const char* path = "/Users/tmori/project/oss/hakoniwa-unreal-simasset-plugin/plugin/custom.json";
    int ret = hako_asset_register("UnrealHakoAsset", path, &my_callback, 1000);
    UE_LOG(LogTemp, Warning, TEXT("ret = %d"), ret);
    UE_LOG(LogTemp, Warning, TEXT("InitializeAsset() Exit"));
}

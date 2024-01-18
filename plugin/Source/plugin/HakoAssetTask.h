// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#define HAKO_ASSET_DELTAT_TIME_USEC 1000
/**
 * 
 */
class PLUGIN_API HakoAssetTask : public FRunnable
{
public:
    virtual bool Init() override;
    virtual uint32 Run() override;
    virtual void Stop() override;
    uint64 GetHakoSimTimeUsec();
    uint64 GetAssetSimTimeUsec();
    bool NotifyAssetSimTimeUsec(uint64 asset_simtime_usec);
protected:
};

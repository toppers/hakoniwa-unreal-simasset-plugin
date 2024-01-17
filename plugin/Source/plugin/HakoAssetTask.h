// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

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
    bool NotifyAssetSimTimeUsec(uint64 asset_simtime_usec);
protected:
};

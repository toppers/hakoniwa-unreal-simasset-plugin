// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HakoAsset.h"
#include "HakoActorRoot.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLUGIN_API UHakoActorRoot : public UActorComponent
{
	GENERATED_BODY()

	HakoAsset* hako_module;
	uint64 asset_simtime_usec;
public:	
	// Sets default values for this component's properties
	UHakoActorRoot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

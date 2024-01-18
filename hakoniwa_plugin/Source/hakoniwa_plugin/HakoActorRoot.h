// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HakoAssetModule.h"
#include "HakoActorRoot.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HAKONIWA_PLUGIN_API UHakoActorRoot : public UActorComponent
{
	GENERATED_BODY()
	HakoAssetModule* hako_module;
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

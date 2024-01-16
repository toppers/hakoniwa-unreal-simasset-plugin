// Fill out your copyright notice in the Description page of Project Settings.


#include "HakoActorRoot.h"
#include "Logging/LogMacros.h"
#include "Misc/OutputDevice.h"

// Sets default values for this component's properties
UHakoActorRoot::UHakoActorRoot()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHakoActorRoot::BeginPlay()
{
	Super::BeginPlay();
	IModuleInterface* plugin = FModuleManager::Get().LoadModule("plugin");
	if (plugin == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("can not get plugin"));
	}
	else {
		HakoAsset* hako_module = FModuleManager::GetModulePtr<HakoAsset>("plugin");
		if (hako_module != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Loaded HakoAsset"));
			hako_module->InitializeAsset();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("can not get HakoAsset"));
		}
	}
}


// Called every frame
void UHakoActorRoot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

}


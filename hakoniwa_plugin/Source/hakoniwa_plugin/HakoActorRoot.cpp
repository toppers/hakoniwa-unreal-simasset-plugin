// Fill out your copyright notice in the Description page of Project Settings.


#include "HakoActorRoot.h"
#include "Logging/LogMacros.h"
#include "Misc/OutputDevice.h"
#include "geometry_msgs/pdu_ctype_Twist.h"

// Sets default values for this component's properties
UHakoActorRoot::UHakoActorRoot()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHakoActorRoot::BeginPlay()
{
	Super::BeginPlay();
	IModuleInterface* plugin = FModuleManager::Get().LoadModule("hakoniwa_plugin");
	if (plugin == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("can not get hakoiwa_plugin"));
	}
	else {
		hako_module = FModuleManager::GetModulePtr<HakoAssetModule>("hakoniwa_plugin");
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
#if 0
	if (hako_module != nullptr) {
		uint64 delta_simtime_usec = static_cast<uint64>(DeltaTime * 1000000.0);
		if (hako_module->NotifyAssetSimTimeUsec(delta_simtime_usec)) {
			FString RoboName = "DroneAvator";
			HakoPduChannelIdType Channel = 1;
			char Buffer[48];
			int ret = hako_module->ReadPdu(RoboName, Channel, Buffer, sizeof(Buffer));
			Hako_Twist *pos = (Hako_Twist*)(Buffer);
			FVector NewLocation(pos->linear.x * 100.0f, -pos->linear.y * 100.0f, pos->linear.z * 100.0f);

			FRotator NewRotation(
				FMath::RadiansToDegrees(pos->angular.y),
				FMath::RadiansToDegrees(pos->angular.z),
				FMath::RadiansToDegrees(pos->angular.x)
			);
			AActor* ParentActor = GetOwner();
			if (ParentActor)
			{
				ParentActor->SetActorLocation(NewLocation);
				ParentActor->SetActorRotation(NewRotation);
			}

		}
		else {
			// can not step next so skip...
		}
	}
#endif

}
void UHakoActorRoot::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
	UE_LOG(LogTemp, Warning, TEXT("EndPlay"));
	if (hako_module != nullptr)
	{
		hako_module->FinalizeAsset();
		hako_module = nullptr;
	}
	
}


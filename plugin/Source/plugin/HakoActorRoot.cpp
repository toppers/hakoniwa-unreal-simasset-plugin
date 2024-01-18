// Fill out your copyright notice in the Description page of Project Settings.


#include "HakoActorRoot.h"
#include "Logging/LogMacros.h"
#include "Misc/OutputDevice.h"
#include "geometry_msgs/pdu_ctype_Twist.h"

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
	asset_simtime_usec = 0;
	IModuleInterface* plugin = FModuleManager::Get().LoadModule("plugin");
	if (plugin == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("can not get plugin"));
	}
	else {
		hako_module = FModuleManager::GetModulePtr<HakoAsset>("plugin");
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
	uint64 delta_simtime_usec = static_cast<uint64>(DeltaTime * 1000000.0);
	//uint64 delta_simtime_usec = 1000; /* 1msec */
	uint64 next_simtime_usec = asset_simtime_usec + delta_simtime_usec;
	//UE_LOG(LogTemp, Log, TEXT("DeltaTime: %f"), DeltaTime);
	//UE_LOG(LogTemp, Log, TEXT("asset_simtime_usec: %llu"), asset_simtime_usec);
	//UE_LOG(LogTemp, Log, TEXT("delta_simtime_usec: %llu"), delta_simtime_usec);
	//UE_LOG(LogTemp, Log, TEXT("next_simtime_usec: %llu"), next_simtime_usec);
	if (hako_module != nullptr) {
		if (asset_simtime_usec < hako_module->GetHakoSimTimeUsec()) {
			asset_simtime_usec = next_simtime_usec;
			hako_module->NotifyAssetSimTimeUsec(asset_simtime_usec);
			//UE_LOG(LogTemp, Log, TEXT("NotifyAssetSimTimeUsec() return true: DeltaTime: %f"), DeltaTime);
			//TODO simulation task
			FString RoboName = "DroneAvator";
			HakoPduChannelIdType Channel = 1;
			char Buffer[48];
			int ret = hako_module->ReadPdu(RoboName, Channel, Buffer, sizeof(Buffer));
			//UE_LOG(LogTemp, Warning, TEXT("ReadPdu ret: %d"), ret);
			Hako_Twist *pos = (Hako_Twist*)(Buffer);
			//UE_LOG(LogTemp, Warning, TEXT("ReadPdu pos: %f %f %f"), pos->linear.x, pos->linear.y, pos->linear.z);
			//UE_LOG(LogTemp, Warning, TEXT("ReadPdu rot: %f %f %f"), pos->angular.x, pos->angular.y, pos->angular.z);
			// 位置の設定
			FVector NewLocation(pos->linear.x * 100.0f, -pos->linear.y * 100.0f, pos->linear.z * 100.0f);

			// 姿勢の設定
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
}
void UHakoActorRoot::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
	UE_LOG(LogTemp, Warning, TEXT("EndPlay"));
    // クリーンアップやリソース解放の処理をここに追加
    // 例: スレッドの停止、メモリの解放など
	hako_module->FinalizeAsset();
	hako_module = nullptr;
	
}


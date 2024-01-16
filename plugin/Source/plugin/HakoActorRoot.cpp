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
    UE_LOG(LogTemp, Warning, TEXT("HELLO WORLD!!"));
	
}


// Called every frame
void UHakoActorRoot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

}


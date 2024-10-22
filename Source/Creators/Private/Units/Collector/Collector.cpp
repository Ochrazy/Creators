// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "Collector.h"
#include "CollectorBase.h"


// Sets default values
ACollector::ACollector()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

// Called when the game starts or when spawned
void ACollector::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACollector::AddResources(int inNumResources)
{
	NumResources += inNumResources;
}

void ACollector::EmptyResources()
{	
	NumResources = 0;
}

int ACollector::GetNumResources()
{
	return NumResources;
}

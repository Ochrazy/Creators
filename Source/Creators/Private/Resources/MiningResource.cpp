// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "MiningResource.h"


// Sets default values
AMiningResource::AMiningResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	CurrentResources = 1000;
}

// Called when the game starts or when spawned
void AMiningResource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMiningResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMiningResource::OnDepleted()
{
	Destroy();
}
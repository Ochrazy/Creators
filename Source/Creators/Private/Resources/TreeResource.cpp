// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "TreeResource.h"

// Sets default values
ATreeResource::ATreeResource()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	CurrentResources = 1000;
}

// Called when the game starts or when spawned
void ATreeResource::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATreeResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATreeResource::OnDepleted()
{
	Destroy();
}

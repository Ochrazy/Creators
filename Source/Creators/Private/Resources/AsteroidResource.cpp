// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "AsteroidResource.h"

// Sets default values
AAsteroidResource::AAsteroidResource()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	CurrentResources = 10000;
}

// Called when the game starts or when spawned
void AAsteroidResource::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAsteroidResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAsteroidResource::OnDepleted()
{
	Destroy();
}



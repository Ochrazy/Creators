// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "MiningResource.h"


// Sets default values
AMiningResource::AMiningResource()
	: ResourcesLeft(1000)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
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

void AMiningResource::ResetResource(bool UnhideInGame)
{
	ResourcesLeft = GetClass()->GetDefaultObject<AMiningResource>()->ResourcesLeft;
	if (UnhideInGame)
	{
		SetActorHiddenInGame(false);
	}
}

int32 AMiningResource::RetrieveResources(int32 amount)
{
	ResourcesLeft -= amount;

	if (ResourcesLeft <= 0)
	{
		OnDepleted();

		// Return actually retrieved Resources
		return amount + ResourcesLeft;
	}
	
	return amount;
}

int32 AMiningResource::GetAvailableResources() const
{
	return ResourcesLeft;
}

int32 AMiningResource::GetInitialResources() const
{
	return GetClass()->GetDefaultObject<AMiningResource>()->GetAvailableResources();
}

void AMiningResource::OnDepleted()
{
	Destroy();
}



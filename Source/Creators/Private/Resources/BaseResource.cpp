// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "BaseResource.h"


// Sets default values
ABaseResource::ABaseResource()
	: CurrentResources(1000)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ABaseResource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseResource::ResetResource(bool UnhideInGame)
{
	CurrentResources = GetClass()->GetDefaultObject<ABaseResource>()->CurrentResources;
	if (UnhideInGame)
	{
		SetActorHiddenInGame(false);
	}
}

int32 ABaseResource::RetrieveResources(int32 amount)
{
	CurrentResources -= amount;

	if (CurrentResources <= 0)
	{
		OnDepleted();

		// Return actually retrieved Resources
		return amount + CurrentResources;
	}

	return amount;
}

int32 ABaseResource::GetAvailableResources() const
{
	return CurrentResources;
}

int32 ABaseResource::GetInitialResources() const
{
	return GetClass()->GetDefaultObject<ABaseResource>()->GetAvailableResources();
}

void ABaseResource::OnDepleted()
{

}

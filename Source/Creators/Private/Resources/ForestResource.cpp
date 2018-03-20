// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "ForestResource.h"
#include "TreeResource.h"


// Sets default values
AForestResource::AForestResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Trees = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Trees"));
}

// Called when the game starts or when spawned
void AForestResource::BeginPlay()
{
	Super::BeginPlay();
	
}

ATreeResource* AForestResource::AddTree(const FTransform& inTransform)
{
	auto TreeResource = GetWorld()->SpawnActor<ATreeResource>(ATreeResource::StaticClass(), inTransform);
	if (TreeResource != nullptr)
	{
		TreeResources.Add(TreeResource);
		Trees->AddInstance(inTransform);
		TreeResource->Init(Trees, TreeResources.Num()-1);
	}

	return TreeResource;
}

void AForestResource::RemoveTree(ATreeResource* inTree)
{

}


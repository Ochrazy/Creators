// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "InstancedBaseResource.h"

// Sets default values
AInstancedBaseResource::AInstancedBaseResource()
	: InstancedMesh(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	this->Mesh->SetActive(false);
}

AInstancedBaseResource::AInstancedBaseResource(TWeakObjectPtr<UInstancedStaticMeshComponent> inInstancedResource)
	: InstancedMesh(inInstancedResource)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	this->Mesh->SetActive(false);
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "TreeResource.h"
#include "CreatorsBaseActor.h"

// Sets default values
ATreeResource::ATreeResource()
	: Age(0.f), InstanceID(-1), InstancedForestMesh(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CurrentResources = 1000;

	this->Mesh->SetActive(false);
}

// Called when the game starts or when spawned
void ATreeResource::BeginPlay()
{
	Super::BeginPlay();
}

void ATreeResource::Init(UInstancedStaticMeshComponent* inInstancedMesh, int inInstanceID)
{
	InstancedForestMesh = inInstancedMesh;
	InstanceID = inInstanceID;

	FTransform oldTrans;
	InstancedForestMesh->GetInstanceTransform(InstanceID, oldTrans, false);
	oldTrans.AddToTranslation(FVector(0.f, 0.f, -100.f));
	InstancedForestMesh->UpdateInstanceTransform(InstanceID, oldTrans, false, true, true);
}

// Called every frame
void ATreeResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Age += DeltaTime;

	if (Age < 6)
	{
		FTransform oldTrans;
		InstancedForestMesh->GetInstanceTransform(InstanceID, oldTrans, false);

		oldTrans.AddToTranslation(FVector(0.f, 0.f, 20.f * DeltaTime));
		InstancedForestMesh->UpdateInstanceTransform(InstanceID, oldTrans, false, true, true);
	}
}

void ATreeResource::OnDepleted()
{
	Destroy();
}

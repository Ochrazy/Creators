// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "TreeResource.h"
#include "CreatorsBaseActor.h"

// Sets default values
ATreeResource::ATreeResource()
	: Age(0.f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CurrentResources = 1000;

	Trees = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Trees"));
	this->Mesh->DestroyComponent();
	RootComponent = Trees;
}

// Called when the game starts or when spawned
void ATreeResource::BeginPlay()
{
	Super::BeginPlay();

	//Trees = NewObject<UInstancedStaticMeshComponent>(this);
	//Trees->RegisterComponent();
	//Trees->SetStaticMesh(Cast<ACreatorsBaseActor>(this)->Mesh);
	//Trees->SetFlags(RF_Transactional);
	//this->AddInstanceComponent(Trees);
}

// Called every frame
void ATreeResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AddActorLocalOffset(FVector(0.f, 0.f, 20.f * DeltaTime));
	Age += DeltaTime;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATreeResource::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		ATreeResource* treeResource = Cast<ATreeResource>(FoundActors[0]);
		int count = treeResource->Trees->GetInstanceCount();
		for (int i = 0; i < count; i++)
		{
			FTransform oldTrans; 
			treeResource->Trees->GetInstanceTransform(i, oldTrans, false);
			oldTrans.AddToTranslation(FVector(0.f, 0.f, 20.f * DeltaTime));
			treeResource->Trees->UpdateInstanceTransform(i, oldTrans, false, true, true);
		}
	}
}

void ATreeResource::OnDepleted()
{
	Destroy();
}

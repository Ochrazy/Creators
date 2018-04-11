// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include <chrono>
#include "Runtime/Engine/Private/InstancedStaticMesh.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "InstancedBaseResource.h"

// Sets default values
AInstancedBaseResource::AInstancedBaseResource()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Trees[0] = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Trees"));
	Trees[1] = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Trees1"));
	Trees[2] = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Trees2"));
	Trees[3] = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Trees3"));

	whatToUpdate = 0;

	this->Mesh->SetActive(false);
}

// Called when the game starts or when spawned
void AInstancedBaseResource::BeginPlay()
{
	Super::BeginPlay();

	FTransform transf;
	transf.SetIdentity();

	float scaling = 20;

	for (int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			transf.SetTranslation(FVector(GetActorLocation().X + (x * scaling), GetActorLocation().Y + (y * scaling), GetActorLocation().Z));
			transf.SetScale3D(FVector(0.1f, 0.1f, 0.1f));
			Trees[0]->AddInstance(transf);
			age.push_back(0);
		}
	}

	for (int x = 210; x < 310; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			transf.SetTranslation(FVector(GetActorLocation().X + (x * scaling), GetActorLocation().Y + (y * scaling), GetActorLocation().Z));
			transf.SetScale3D(FVector(0.1f, 0.1f, 0.1f));
			Trees[1]->AddInstance(transf);
		}
	}

	for (int x = 0; x < 100; x++)
	{
		for (int y = 210; y < 310; y++)
		{
			transf.SetTranslation(FVector(GetActorLocation().X + (x * scaling), GetActorLocation().Y + (y * scaling), GetActorLocation().Z));
			transf.SetScale3D(FVector(0.1f, 0.1f, 0.1f));
			Trees[2]->AddInstance(transf);
		}
	}

	for (int x = 210; x < 310; x++)
	{
		for (int y = 210; y < 310; y++)
		{
			transf.SetTranslation(FVector(GetActorLocation().X + (x * scaling), GetActorLocation().Y + (y * scaling), GetActorLocation().Z));
			transf.SetScale3D(FVector(0.1f, 0.1f, 0.1f));
			Trees[3]->AddInstance(transf);
		}
	}

	//FTimerDelegate TimerDel;
	//FTimerHandle TimerHandle;
	//TimerDel.BindUFunction(this, FName("timerHandle"), 1);

	////Calling MyUsefulFunction after 5 seconds with looping
	//GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, 3.f, true, 1.f);

	//FTimerDelegate TimerDel2;
	//FTimerHandle TimerHandle2;
	//TimerDel2.BindUFunction(this, FName("timerHandle"), 2);
	//GetWorldTimerManager().SetTimer(TimerHandle2, TimerDel2, 3.f, true, 2.f);

	//FTimerDelegate TimerDel3;
	//FTimerHandle TimerHandle3;
	//TimerDel3.BindUFunction(this, FName("timerHandle"), 3);
	//GetWorldTimerManager().SetTimer(TimerHandle3, TimerDel3, 3.f, true, 3.f);
}

void AInstancedBaseResource::timerHandle(int index)
{
	/*int count = Trees->GetInstanceCount();
	for (int i = (count / 3) * (index-1); i < (count / 3) * index; i++)
	{
		age[i] += 2.f;
		if (age[i] < 26.f)
		{
			FTransform oldTrans;
			Trees->GetInstanceTransform(i, oldTrans, false);

			oldTrans.AddToTranslation(FVector(0.f, 0.f, 20.f * 2.f));

			if (i == (count / 3) * index - 1)
				Trees->UpdateInstanceTransform(i, oldTrans, false, true, true);
			else Trees->UpdateInstanceTransform(i, oldTrans, false, false, true);
		}
	}*/
}

// Called every frame
void AInstancedBaseResource::Tick(float DeltaTime)
{
	//auto start = std::chrono::high_resolution_clock::now();

	/*for (int whatToUpdate = 0; whatToUpdate < 4; ++whatToUpdate)
	{*/
		int count = Trees[whatToUpdate]->GetInstanceCount();

		for (int i = 0; i < (count); i++)
		{
			age[i] += DeltaTime;
			//if (age[i] < 6.f)
			{
				/*FTransform oldTrans;
				Trees[whatToUpdate]->GetInstanceTransform(i, oldTrans, false);
				oldTrans.AddToTranslation(FVector(0.f, 100.f * DeltaTime, 0.f));
				Trees[whatToUpdate]->UpdateInstanceTransform(i, oldTrans, false, false, true);	*/

				Trees[whatToUpdate]->PerInstanceSMData[i].Transform.M[3][1] += 100.f * DeltaTime;

				//NewInstanceBounds = Trees[whatToUpdate]->GetStaticMesh()->GetBounds().GetBox().MoveTo(Trees[whatToUpdate]->PerInstanceSMData[Trees[whatToUpdate]->SortedInstances[i]].Transform.GetOrigin());
				//Trees[whatToUpdate]->UnbuiltInstanceBounds += NewInstanceBounds;
				//bounds[Trees[whatToUpdate]->SortedInstances[i]] = NewInstanceBounds;


				//// Update existing BodyInstance
				//FTransform tran;
				//tran.SetLocation(FVector(Trees->PerInstanceSMData[i].Transform.M[3][0], 
				//	Trees->PerInstanceSMData[i].Transform.M[3][1], Trees->PerInstanceSMData[i].Transform.M[3][2]));

				//Trees->InstanceBodies[i]->SetBodyTransform(tran, TeleportFlagToEnum(true));

			/*	Trees->InstanceBodies[i]->UpdateBodyScale(FVector(Trees->PerInstanceSMData[i].Transform.M[0][0],
					Trees->PerInstanceSMData[i].Transform.M[1][1], Trees->PerInstanceSMData[i].Transform.M[2][2]));*/
			}
		}
		for (auto& node : *Trees[whatToUpdate]->ClusterTreePtr.Get())
		{
			node.BoundMin.Y += 100.f * DeltaTime;
			node.BoundMax.Y += 100.f * DeltaTime;
		}

		if(Trees[whatToUpdate]->ClusterTreePtr.IsValid())
			Trees[whatToUpdate]->BuiltInstanceBounds = FBox((*Trees[whatToUpdate]->ClusterTreePtr)[0].BoundMin, (*Trees[whatToUpdate]->ClusterTreePtr)[0].BoundMax);

		//delete[] bounds;

		//if (!Trees[whatToUpdate]->IsAsyncBuilding())
		{
			//Trees[whatToUpdate]->UnbuiltInstanceBoundsList.Add(std::move(Trees[whatToUpdate]->UnbuiltInstanceBounds));
			//Trees[whatToUpdate]->BuiltInstanceBounds = std::move(Trees[whatToUpdate]->UnbuiltInstanceBounds);
			//Trees[whatToUpdate]->BuildTreeIfOutdated(true, false);
		}
		//Trees[whatToUpdate]->ClusterTreePtr.Get()..BoundMin = FVector(0,0,0);
		/*Trees[whatToUpdate]->ReleasePerInstanceRenderData();
		Trees[whatToUpdate]->InitPerInstanceRenderData(true);*/
		//Trees->InitPerInstanceRenderData(true, Trees->PerInstanceRenderData->InstanceBuffer.UpdateInstanceData();
		
		Trees[whatToUpdate]->PerInstanceRenderData->InstanceBuffer.UpdateInstanceData(Trees[whatToUpdate], 0, count);
		Trees[whatToUpdate]->MarkRenderStateDirty();

		//Trees->PerInstanceRenderData->InstanceBuffer.UpdateInstanceData(Trees, Trees->PerInstanceRenderData->HitProxies, 0, 100, false);
		//Trees[whatToUpdate]->MarkRenderStateDirty();
		//UNavigationSystem::UpdateComponentInNavOctree(*Trees);

	
	//}

		whatToUpdate++;
		if (whatToUpdate > 3) whatToUpdate = 0;

	//auto end = std::chrono::high_resolution_clock::now();
	//auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("valuesS: %d"), time.count()));
}

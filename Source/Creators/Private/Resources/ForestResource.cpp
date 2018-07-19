// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "ForestResource.h"
#include "TreeResource.h"
#include <chrono>
#include "Runtime/Engine/Private/InstancedStaticMesh.h"

template<typename F>
struct FInstanceTransformMatrix
{
	F InstanceTransform1[4];
	F InstanceTransform2[4];
	F InstanceTransform3[4];

	friend FArchive& operator<<(FArchive& Ar, FInstanceTransformMatrix& V)
	{
		return Ar
			<< V.InstanceTransform1[0]
			<< V.InstanceTransform1[1]
			<< V.InstanceTransform1[2]
			<< V.InstanceTransform1[3]

			<< V.InstanceTransform2[0]
			<< V.InstanceTransform2[1]
			<< V.InstanceTransform2[2]
			<< V.InstanceTransform2[3]

			<< V.InstanceTransform3[0]
			<< V.InstanceTransform3[1]
			<< V.InstanceTransform3[2]
			<< V.InstanceTransform3[3];
	}

};
//
//template<typename Tag, typename Tag::type M>
//struct Rob {
//	friend typename Tag::type get(Tag) {
//		return M;
//	}
//};
//
//// tag used to access A::a
//struct A_f {
//	typedef TSharedPtr<FStaticMeshInstanceData, ESPMode::ThreadSafe> FStaticMeshInstanceBuffer::*type;
//	friend type get(A_f);
//};
//
//template struct Rob<A_f, &FStaticMeshInstanceBuffer::InstanceData>;

// Sets default values
AForestResource::AForestResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Trees = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Trees"));
	RootComponent = Trees;
}

// Called when the game starts or when spawned
void AForestResource::BeginPlay()
{
	Super::BeginPlay();

	/*FTransform transf;
	transf.SetIdentity();

	float scaling = 20;

	for (int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 200; y++)
		{
			transf.SetTranslation(FVector(GetActorLocation().X + (x * scaling), GetActorLocation().Y + (y * scaling), GetActorLocation().Z));
			transf.SetScale3D(FVector(0.1f, 0.1f, 0.1f));
			AddTree(transf);
		}
	}*/
}

void AForestResource::AddTree(const FTransform& inTransform)
{
	TSharedPtr<FPerInstanceRenderData, ESPMode::ThreadSafe> fds; fds.Get();
	int count = Trees->GetInstanceCount();
	FStaticMeshInstanceData* InstanceData = Trees->PerInstanceRenderData->InstanceBuffer.GetInstanceData(); //*get(A_f());
	if (InstanceData && InstanceData->GetNumInstances() > 0)
	{
		FVector4* rarray = const_cast<FVector4*>(reinterpret_cast<const FVector4*>(InstanceData->GetOriginResourceArray()->GetResourceData()));
		FInstanceTransformMatrix<FFloat16>* itarray =
			const_cast<FInstanceTransformMatrix<FFloat16>*>(reinterpret_cast<const FInstanceTransformMatrix<FFloat16>*>(InstanceData->GetTransformResourceArray()->GetResourceData()));
	/*	for (int i = 0; i < (count); i++)
		{
			if (i < Trees->InstanceReorderTable.Num())
			{
				Trees->PerInstanceSMData[i].Transform.M[3][2] = rarray[Trees->InstanceReorderTable[i]].Z;
			}
			else
			{
				Trees->PerInstanceSMData[i].Transform.M[3][2] = rarray[Trees->InstanceReorderTable[i]].Z;
			}
		}*/
	}
	FTransform tmp = inTransform;
	tmp.AddToTranslation(FVector(0, 0, -100));
	Trees->AddInstance(tmp);
	age.push_back(0);
	/*auto TreeResource = GetWorld()->SpawnActorDeferred<ATreeResource>(ATreeResource::StaticClass(), inTransform);
	if (TreeResource != nullptr)
	{
		TreeResources.Add(TreeResource);
		Trees->AddInstance(inTransform);
		TreeResource->Init(Trees, TreeResources.Num()-1);
		TreeResource->FinishSpawning(inTransform);
	}

	return TreeResource;*/
}

void AForestResource::RemoveTree(int inTreeID)
{
	int count = Trees->GetInstanceCount();
	
	if (count > 0)
	{
		//// Remove by swap and pop -> Result is already reordered. 
		//// Does not preserve original order (Index of last instance changed)
		//// Way faster than reordering. Might need to update index if saved elsewhere.
		//std::iter_swap(age.begin() + inTreeID, age.end() - 1);
		//age.pop_back();
		age.erase(age.begin() + inTreeID);

	/*	FStaticMeshInstanceData* InstanceData = Trees->PerInstanceRenderData->InstanceBuffer.GetInstanceData();
		InstanceData->SwapInstance(inTreeID, count - 1);
		InstanceData->NullifyInstance(count - 1);

		Trees->InstanceReorderTable.Pop();

		Trees->PerInstanceSMData.RemoveAtSwap(inTreeID);
		Trees->InstanceBodies[inTreeID]->TermBody();
		Trees->InstanceBodies.RemoveAtSwap(inTreeID);*/
		Trees->RemoveInstance(inTreeID);

		TreesToCut.Remove(inTreeID);	
	}
}

FTreeInstance AForestResource::GetNearestTreeToCut(const FVector& originLocation) const
{
	/*FStaticMeshInstanceData* InstanceData = Trees->PerInstanceRenderData->InstanceBuffer.GetInstanceData();
	FVector4* rarray = const_cast<FVector4*>(reinterpret_cast<const FVector4*>(InstanceData->GetOriginResourceArray()->GetResourceData()));*/
	
	// Find Nearest Tree Instance
	int nearestID = -1;
	float nearestDist = 0.f;
	
	for (auto& treeID : TreesToCut)
	{
		FTransform transf;
		Trees->GetInstanceTransform(treeID, transf);

		if (nearestID == -1)
		{
			nearestID = treeID;
			nearestDist = FVector::DistSquared(originLocation, transf.GetLocation());
		}
		else
		{
			float currentDist = FVector::DistSquared(originLocation, transf.GetLocation());
			if (currentDist < nearestDist)
			{
				nearestID = treeID;
				nearestDist = currentDist;
			}
		}
	}

	FTransform nearestTransf;
	Trees->GetInstanceTransform(nearestID, nearestTransf);
	return FTreeInstance(nearestID, Trees->GetComponentLocation() + nearestTransf.GetLocation());
}

// Called every frame
void AForestResource::Tick(float DeltaTime)
{
	int countBefore = Trees->InstanceReorderTable.Num();
	FStaticMeshInstanceData* InstanceData = Trees->PerInstanceRenderData->InstanceBuffer.GetInstanceData();
	if (InstanceData && InstanceData->GetNumInstances() > 0)
	{
			FVector4* rarray = const_cast<FVector4*>(reinterpret_cast<const FVector4*>(InstanceData->GetOriginResourceArray()->GetResourceData()));
			FInstanceTransformMatrix<FFloat16>* itarray =
				const_cast<FInstanceTransformMatrix<FFloat16>*>(reinterpret_cast<const FInstanceTransformMatrix<FFloat16>*>(InstanceData->GetTransformResourceArray()->GetResourceData()));
			
			for (int i = 0; i < age.size(); i++)//(countBefore); i++)
			{
				
					age[i] += DeltaTime;
					if (age[i] > 8.f)
					{
						TreesToCut.Add(i);
					//	// Remove by swap and pop -> Result is already reordered. 
					//	// Does not preserve original order (Index of last instance changed)
					//	// Way faster than reordering. Might need to update index if saved elsewhere.
					//	std::iter_swap(age.begin() + i, age.end() - 1);
					//	age.pop_back();

					//	InstanceData->SwapInstance(i, countBefore - 1);
					//	InstanceData->NullifyInstance(countBefore - 1);

					//	Trees->InstanceReorderTable.Pop();

					//	Trees->PerInstanceSMData.RemoveAtSwap(i);
					//	Trees->InstanceBodies.RemoveAtSwap(i);
					//	
					//	countBefore--;
					//	i--;
					}
			}


			int count = age.size();
		/*	for (int i = 0; i < (count); i++)
			{
				Trees->PerInstanceSMData[i].Transform.M[3][2] = rarray[Trees->InstanceReorderTable[i]].Z;
			}*/
			
			FTransform tmp;

			for (int i = 0; i < (count); i++)
			{
				if (age[i] < 6.f)
				{
					Trees->GetInstanceTransform(i, tmp);
					tmp.SetLocation(tmp.GetLocation() + FVector(0, 0, 20.f * DeltaTime));
					Trees->UpdateInstanceTransform(i, tmp, false, false, false);
					
					//rarray[i].Z += 20.f * DeltaTime;

					//// Update existing BodyInstance
					//FTransform tran;
					//tran.SetLocation(FVector(rarray[i].X + Trees->GetComponentLocation().X,
					//	rarray[i].Y + Trees->GetComponentLocation().Y, rarray[i].Z + Trees->GetComponentLocation().Z));
					//Trees->InstanceBodies[i]->SetBodyTransform(tran, TeleportFlagToEnum(true));

				}
			}

			Trees->MarkRenderStateDirty();
		
	}
}



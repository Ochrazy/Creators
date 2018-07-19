//// Fill out your copyright notice in the Description page of Project Settings.
//
#include "Creators.h"
//#include <chrono>
//#include "Runtime/Engine/Private/InstancedStaticMesh.h"
//#include "Components/InstancedStaticMeshComponent.h"
//#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "InstancedBaseResource.h"
//#include <future>
//
//// Sets default values
//AInstancedBaseResource::AInstancedBaseResource()
//{
//	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//	PrimaryActorTick.bStartWithTickEnabled = true;
//
//	Trees.Add(CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Trees")));
//	Trees.Add(CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Trees1")));
//	Trees.Add(CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Trees2")));
//	Trees.Add(CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Trees3")));
//
//	whatToUpdate = 0;
//	angle = 0;
//
//	this->Mesh->SetActive(false);
//}
//
//// Called when the game starts or when spawned
//void AInstancedBaseResource::BeginPlay()
//{
//	Super::BeginPlay();
//
//	FTransform transf;
//	transf.SetIdentity();
//
//	float scaling = 20;
//
//	for (int x = 0; x < 10; x++)
//	{
//		for (int y = 0; y < 200; y++)
//		{
//			transf.SetTranslation(FVector(GetActorLocation().X + (x * scaling), GetActorLocation().Y + (y * scaling), GetActorLocation().Z));
//			transf.SetScale3D(FVector(0.1f, 0.1f, 0.1f));
//			Trees[0]->AddInstance(transf);
//			age.push_back(0);
//		}
//	}
//
//	for (int x = 210; x < 310; x++)
//	{
//		for (int y = 0; y < 100; y++)
//		{
//			transf.SetTranslation(FVector(GetActorLocation().X + (x * scaling), GetActorLocation().Y + (y * scaling), GetActorLocation().Z));
//			transf.SetScale3D(FVector(0.1f, 0.1f, 0.1f));
//			Trees[1]->AddInstance(transf);
//		}
//	}
//
//	for (int x = 0; x < 100; x++)
//	{
//		for (int y = 210; y < 310; y++)
//		{
//			transf.SetTranslation(FVector(GetActorLocation().X + (x * scaling), GetActorLocation().Y + (y * scaling), GetActorLocation().Z));
//			transf.SetScale3D(FVector(0.1f, 0.1f, 0.1f));
//			Trees[2]->AddInstance(transf);
//		}
//	}
//
//	for (int x = 210; x < 310; x++)
//	{
//		for (int y = 210; y < 310; y++)
//		{
//			transf.SetTranslation(FVector(GetActorLocation().X + (x * scaling), GetActorLocation().Y + (y * scaling), GetActorLocation().Z));
//			transf.SetScale3D(FVector(0.1f, 0.1f, 0.1f));
//			Trees[3]->AddInstance(transf);
//		}
//	}
//
//	constexpr int N = 100000000;
//	
//	auto _start = std::chrono::high_resolution_clock::now();
//	TArray<int> test;
//	test.Reserve(N);
//	for (unsigned int k = 0; k < N; ++k)
//	{
//		test.Add(k);
//	}
//	auto ds = (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - _start)).count();
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("valuesS: %d"), ds));
//
//	_start = std::chrono::high_resolution_clock::now();
//	int * bigarray = new int[N];
//	for (unsigned int k = 0; k < N; ++k)
//	{
//		bigarray[k] = k;
//	}
//	ds = (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - _start)).count();
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("valuesB: %d"), ds));
//	//FTimerDelegate TimerDel;
//	//FTimerHandle TimerHandle;
//	//TimerDel.BindUFunction(this, FName("timerHandle"), 1);
//
//	////Calling MyUsefulFunction after 5 seconds with looping
//	//GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, 3.f, true, 1.f);
//
//	//FTimerDelegate TimerDel2;
//	//FTimerHandle TimerHandle2;
//	//TimerDel2.BindUFunction(this, FName("timerHandle"), 2);
//	//GetWorldTimerManager().SetTimer(TimerHandle2, TimerDel2, 3.f, true, 2.f);
//
//	//FTimerDelegate TimerDel3;
//	//FTimerHandle TimerHandle3;
//	//TimerDel3.BindUFunction(this, FName("timerHandle"), 3);
//	//GetWorldTimerManager().SetTimer(TimerHandle3, TimerDel3, 3.f, true, 3.f);
//}
//
//void AInstancedBaseResource::timerHandle(int index)
//{
//	/*int count = Trees->GetInstanceCount();
//	for (int i = (count / 3) * (index-1); i < (count / 3) * index; i++)
//	{
//		age[i] += 2.f;
//		if (age[i] < 26.f)
//		{
//			FTransform oldTrans;
//			Trees->GetInstanceTransform(i, oldTrans, false);
//
//			oldTrans.AddToTranslation(FVector(0.f, 0.f, 20.f * 2.f));
//
//			if (i == (count / 3) * index - 1)
//				Trees->UpdateInstanceTransform(i, oldTrans, false, true, true);
//			else Trees->UpdateInstanceTransform(i, oldTrans, false, false, true);
//		}
//	}*/
//}
//
////template<typename F>
////struct FInstanceTransformMatrix
////{
////	F InstanceTransform1[4];
////	F InstanceTransform2[4];
////	F InstanceTransform3[4];
////
////	friend FArchive& operator<<(FArchive& Ar, FInstanceTransformMatrix& V)
////	{
////		return Ar
////			<< V.InstanceTransform1[0]
////			<< V.InstanceTransform1[1]
////			<< V.InstanceTransform1[2]
////			<< V.InstanceTransform1[3]
////
////			<< V.InstanceTransform2[0]
////			<< V.InstanceTransform2[1]
////			<< V.InstanceTransform2[2]
////			<< V.InstanceTransform2[3]
////
////			<< V.InstanceTransform3[0]
////			<< V.InstanceTransform3[1]
////			<< V.InstanceTransform3[2]
////			<< V.InstanceTransform3[3];
////	}
////
////};
////
////template<typename Tag, typename Tag::type M>
////struct Rob {
////	friend typename Tag::type get(Tag) {
////		return M;
////	}
////};
////
////// tag used to access A::a
////struct A_f {
////	typedef FStaticMeshInstanceData* FStaticMeshInstanceBuffer::*type;
////	friend type get(A_f);
////};
////
////template struct Rob<A_f, &FStaticMeshInstanceBuffer::InstanceData>;
//
//// Called every frame
//void AInstancedBaseResource::Tick(float DeltaTime)
//{
//	//auto start = std::chrono::high_resolution_clock::now();
//	//if (Trees[whatToUpdate]->ClusterTreePtr.IsValid())
//	//{
//	//	angle += DeltaTime;
//
//	//	float cosA = 0.1f * cos(angle);
//	//	float sinA = 0.1f * sin(angle);
//
//	//	/*for (int whatToUpdate = 0; whatToUpdate < 4; ++whatToUpdate)
//	//	{*/
//
//	//	int count = Trees[whatToUpdate]->GetInstanceCount();
//	//	FStaticMeshInstanceData* InstanceData = Trees[whatToUpdate]->PerInstanceRenderData->InstanceBuffer.*get(A_f());
//
//	//	FVector4* rarray = const_cast<FVector4*>(reinterpret_cast<const FVector4*>(InstanceData->GetOriginResourceArray()->GetResourceData()));
//	//	FInstanceTransformMatrix<FFloat16>* itarray =
//	//		const_cast<FInstanceTransformMatrix<FFloat16>*>(reinterpret_cast<const FInstanceTransformMatrix<FFloat16>*>(InstanceData->GetTransformResourceArray()->GetResourceData()));
//	//	int indexReordered = 0;
//	//	TArray<int32>& reorderArray = Trees[whatToUpdate]->InstanceReorderTable;
//	//	//for (int i = 0; i < (count); i++)
//	//	//{
//	//	//	//indexReordered = reorderArray[i];
//	//	//	if (i < Trees[whatToUpdate]->SortedInstances.Num())
//	//	//		age[Trees[whatToUpdate]->SortedInstances[i]] += DeltaTime;
//	//	//	else age[i] += DeltaTime;
//	//	//}
//
//	//	//if (GetWorld()->GetTimeSeconds() - Trees[whatToUpdate]->LastRenderTimeOnScreen <= DeltaTime*2)
//	//	{
//	//		int count2 = count / 4;
//	//		auto future = std::async(std::launch::async, [count2, &rarray, DeltaTime, this, &itarray, cosA, sinA] {
//	//			for (int i2 = 0; i2 < (count2); i2++)
//	//			{
//	//				//if (age[i] < 6.f)
//	//				{
//	//					/*FTransform oldTrans;
//	//					Trees[whatToUpdate]->GetInstanceTransform(i, oldTrans, false);
//	//					oldTrans.AddToTranslation(FVector(0.f, 100.f * DeltaTime, 0.f));
//	//					Trees[whatToUpdate]->UpdateInstanceTransform(i, oldTrans, false, false, true);	*/
//	//					//Trees[whatToUpdate]->PerInstanceSMData[i].Transform.M[3][1] += 100.f * DeltaTime;
//	//					rarray[i2].X += 10.f * DeltaTime;
//	//					rarray[i2].Y += 50.f * DeltaTime;
//	//					rarray[i2].Z += 25.f * DeltaTime;
//
//	//					itarray[i2].InstanceTransform1[0] = cosA;
//	//					itarray[i2].InstanceTransform1[1] = -sinA;
//	//					itarray[i2].InstanceTransform2[0] = sinA;
//	//					itarray[i2].InstanceTransform2[1] = cosA;
//	//					/*	Trees[whatToUpdate]->PerInstanceSMData[i].Transform.M[0][0] = cosA;
//	//						Trees[whatToUpdate]->PerInstanceSMData[i].Transform.M[0][1] = -sinA;
//	//						Trees[whatToUpdate]->PerInstanceSMData[i].Transform.M[1][0] = sinA;
//	//						Trees[whatToUpdate]->PerInstanceSMData[i].Transform.M[1][1] = cosA;*/
//
//	//						//NewInstanceBounds = Trees[whatToUpdate]->GetStaticMesh()->GetBounds().GetBox().MoveTo(Trees[whatToUpdate]->PerInstanceSMData[Trees[whatToUpdate]->SortedInstances[i]].Transform.GetOrigin());
//	//						//Trees[whatToUpdate]->UnbuiltInstanceBounds += NewInstanceBounds;
//	//						//bounds[Trees[whatToUpdate]->SortedInstances[i]] = NewInstanceBounds;
//
//
//	//						//// Update existing BodyInstance
//	//						//FTransform tran;
//	//						//tran.SetLocation(FVector(Trees->PerInstanceSMData[i].Transform.M[3][0], 
//	//						//	Trees->PerInstanceSMData[i].Transform.M[3][1], Trees->PerInstanceSMData[i].Transform.M[3][2]));
//
//	//						//Trees->InstanceBodies[i]->SetBodyTransform(tran, TeleportFlagToEnum(true));
//
//	//					/*	Trees->InstanceBodies[i]->UpdateBodyScale(FVector(Trees->PerInstanceSMData[i].Transform.M[0][0],
//	//							Trees->PerInstanceSMData[i].Transform.M[1][1], Trees->PerInstanceSMData[i].Transform.M[2][2]));*/
//	//				}
//	//			}
//	//		});
//
//	//		
//
//	//		auto future2 = std::async(std::launch::async, [count, count2, &rarray, DeltaTime, this, &itarray, cosA, sinA] {
//	//			for (int i2 = count2; i2 < (count2*2); i2++)
//	//			{
//	//					rarray[i2].X += 10.f * DeltaTime;
//	//					rarray[i2].Y += 50.f * DeltaTime;
//	//					rarray[i2].Z += 25.f * DeltaTime;
//
//	//					itarray[i2].InstanceTransform1[0] = cosA;
//	//					itarray[i2].InstanceTransform1[1] = -sinA;
//	//					itarray[i2].InstanceTransform2[0] = sinA;
//	//					itarray[i2].InstanceTransform2[1] = cosA;
//	//			}
//	//		});
//	//		
//	//		auto future3 = std::async(std::launch::async, [count, count2, &rarray, DeltaTime, this, &itarray, cosA, sinA] {
//	//			for (int i2 = count2*2; i2 < (count2*3); i2++)
//	//			{
//	//				rarray[i2].X += 10.f * DeltaTime;
//	//				rarray[i2].Y += 50.f * DeltaTime;
//	//				rarray[i2].Z += 25.f * DeltaTime;
//
//	//				itarray[i2].InstanceTransform1[0] = cosA;
//	//				itarray[i2].InstanceTransform1[1] = -sinA;
//	//				itarray[i2].InstanceTransform2[0] = sinA;
//	//				itarray[i2].InstanceTransform2[1] = cosA;
//	//			}
//	//		});
//
//	//		auto future4 = std::async(std::launch::async, [count, count2, &rarray, DeltaTime, this, &itarray, cosA, sinA] {
//	//			for (int i2 = count2*3; i2 < (count2 * 4); i2++)
//	//			{
//	//				rarray[i2].X += 10.f * DeltaTime;
//	//				rarray[i2].Y += 50.f * DeltaTime;
//	//				rarray[i2].Z += 25.f * DeltaTime;
//
//	//				itarray[i2].InstanceTransform1[0] = cosA;
//	//				itarray[i2].InstanceTransform1[1] = -sinA;
//	//				itarray[i2].InstanceTransform2[0] = sinA;
//	//				itarray[i2].InstanceTransform2[1] = cosA;
//	//			}
//	//		});
//
//	//		auto future5 = std::async(std::launch::async, [DeltaTime, this] {
//	//			auto start = std::chrono::high_resolution_clock::now();
//	//			for (auto& node : *Trees[whatToUpdate]->ClusterTreePtr.Get())
//	//			{
//	//				node.BoundMin.X += 10.f * DeltaTime;
//	//				node.BoundMax.X += 10.f * DeltaTime;
//
//	//				node.BoundMin.Y += 50.f * DeltaTime;
//	//				node.BoundMax.Y += 50.f * DeltaTime;
//
//	//				node.BoundMin.Z += 25.f * DeltaTime;
//	//				node.BoundMax.Z += 25.f * DeltaTime;
//	//			}
//	//			Trees[whatToUpdate]->BuiltInstanceBounds = FBox((*Trees[whatToUpdate]->ClusterTreePtr)[0].BoundMin, (*Trees[whatToUpdate]->ClusterTreePtr)[0].BoundMax);
//	//			auto end = std::chrono::high_resolution_clock::now();
//	//			auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
//	//			//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("values2: %f"), time.count()));
//
//	//		});
//
//	//		future.get();
//	//		future2.get();
//	//		future3.get();
//	//		future4.get();
//	//		future5.get();
//	//		Trees[whatToUpdate]->MarkRenderStateDirty();
//	//	}
//
//	//	//delete[] bounds;
//
//	//	//if (!Trees[whatToUpdate]->IsAsyncBuilding())
//	//	//{
//	//		//Trees[whatToUpdate]->UnbuiltInstanceBoundsList.Add(std::move(Trees[whatToUpdate]->UnbuiltInstanceBounds));
//	//		//Trees[whatToUpdate]->BuiltInstanceBounds = std::move(Trees[whatToUpdate]->UnbuiltInstanceBounds);
//	//		//Trees[whatToUpdate]->BuildTreeIfOutdated(true, false);
//	//	//}
//	//	//Trees[whatToUpdate]->ClusterTreePtr.Get()..BoundMin = FVector(0,0,0);
//	//	/*Trees[whatToUpdate]->ReleasePerInstanceRenderData();
//	//	Trees[whatToUpdate]->InitPerInstanceRenderData(true);*/
//	//	//Trees->InitPerInstanceRenderData(true, Trees->PerInstanceRenderData->InstanceBuffer.UpdateInstanceData();
//
//	//	//Trees[whatToUpdate]->PerInstanceRenderData->InstanceBuffer.UpdateInstanceData(Trees[whatToUpdate], 0, count);
//
//
//	//	//Trees->PerInstanceRenderData->InstanceBuffer.UpdateInstanceData(Trees, Trees->PerInstanceRenderData->HitProxies, 0, 100, false);
//	//	//Trees[whatToUpdate]->MarkRenderStateDirty();
//	//	//UNavigationSystem::UpdateComponentInNavOctree(*Trees);
//
//
//	////}
//
//	//	auto end = std::chrono::high_resolution_clock::now();
//	//	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
//	//	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("valuesS: %d"), time.count()));
//
//	//	whatToUpdate++;
//	//	if (whatToUpdate > 0) whatToUpdate = 0;
//
//	//	
//	//}
//}

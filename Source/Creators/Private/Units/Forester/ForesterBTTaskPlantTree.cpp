// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "ForesterBTTaskPlantTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "CollectorAIController.h"
#include "Forester.h"
#include "TreeResource.h"

UForesterBTTaskPlantTree::UForesterBTTaskPlantTree(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Plant Tree";

	// accept only actors and vectors
	NearestPlantSpot.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UForesterBTTaskPlantTree, NearestPlantSpot));
}

void UForesterBTTaskPlantTree::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (BBAsset)
	{
		NearestPlantSpot.ResolveSelectedKey(*BBAsset);
	}
	else
	{
		UE_LOG(LogBehaviorTree, Warning, TEXT("Can't initialize task: %s, make sure that behavior tree specifies blackboard asset!"), *GetName());
	}
}

EBTNodeResult::Type UForesterBTTaskPlantTree::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FVector plantSpot = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(NearestPlantSpot.GetSelectedKeyID());

	ACollectorAIController* caiController = Cast<ACollectorAIController>(OwnerComp.GetAIOwner());
	if (caiController)
	{
		AForester* forester = Cast<AForester>(caiController->GetPawn());
		if (forester)
		{
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATreeResource::StaticClass(), FoundActors);

			if (FoundActors.Num() == 0)
			{
				ATreeResource* treeResource;
				treeResource = GetWorld()->SpawnActor<ATreeResource>(forester->TreeToSpawnClass, plantSpot, FRotator(0.0, 0.0, 0.0));
				if (treeResource)
				{
					treeResource->Trees->AddInstance(FTransform(FRotator(0.f), plantSpot - treeResource->GetActorLocation(), FVector(2.0, 2.0, 2.0)));
					return EBTNodeResult::Succeeded;
				}
			}
			else
			{
				ATreeResource* treeResource = Cast<ATreeResource>(FoundActors[0]);
				treeResource->Trees->AddInstance(FTransform(FRotator(0.f), plantSpot - treeResource->GetActorLocation(), FVector(2.0, 2.0, 2.0)));
			}

		}
	}

	return EBTNodeResult::Failed;
}

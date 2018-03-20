// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "ForesterBTTaskPlantTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "CollectorAIController.h"
#include "Forester.h"
#include "ForestResource.h"
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
	ACollectorAIController* caiController = Cast<ACollectorAIController>(OwnerComp.GetAIOwner());
	if (caiController)
	{
		AForester* forester = Cast<AForester>(caiController->GetPawn());
		if (forester)
		{
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AForestResource::StaticClass(), FoundActors);

			FVector plantSpot = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(NearestPlantSpot.GetSelectedKeyID());

			AForestResource* forestResource(nullptr);
			if (FoundActors.Num() == 0)
			{				
				forestResource = GetWorld()->SpawnActor<AForestResource>(forester->TreeToSpawnClass, plantSpot, FRotator(0.0, 0.0, 0.0));
			}
			else
			{
				forestResource = Cast<AForestResource>(FoundActors[0]);
			}

			if (forestResource)
			{
				forestResource->AddTree(FTransform(FRotator(0.f), plantSpot - forestResource->GetActorLocation(), FVector(2.0, 2.0, 2.0)));
				return EBTNodeResult::Succeeded;
			}

		}
	}

	return EBTNodeResult::Failed;
}

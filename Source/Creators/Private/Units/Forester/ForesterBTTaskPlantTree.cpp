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
	if (caiController == nullptr)
		return EBTNodeResult::Failed;
	else
	{
		AForester* forester = Cast<AForester>(caiController->GetPawn());
		if (forester == nullptr)
			return EBTNodeResult::Failed;
		else
		{
			ATreeResource* treeResource;
			treeResource = GetWorld()->SpawnActor<ATreeResource>(forester->TreeToSpawnClass, plantSpot, FRotator(0.0, 0.0, 0.0));

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Succeeded;
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "CollectorAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Forester.h"
#include "ForestResource.h"
#include "ForesterBTTaskFindTreeToCut.h"

UForesterBTTaskFindTreeToCut::UForesterBTTaskFindTreeToCut(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Find Tree To Cut";

	// accept only actors and vectors
	NearestTreeToCutID.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UForesterBTTaskFindTreeToCut, NearestTreeToCutID));
	NearestTreeToCutSpot.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UForesterBTTaskFindTreeToCut, NearestTreeToCutSpot));
}

void UForesterBTTaskFindTreeToCut::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (BBAsset)
	{
		NearestTreeToCutID.ResolveSelectedKey(*BBAsset);
		NearestTreeToCutSpot.ResolveSelectedKey(*BBAsset);
	}
	else
	{
		UE_LOG(LogBehaviorTree, Warning, TEXT("Can't initialize task: %s, make sure that behavior tree specifies blackboard asset!"), *GetName());
	}
}

EBTNodeResult::Type UForesterBTTaskFindTreeToCut::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACollectorAIController* caiController = Cast<ACollectorAIController>(OwnerComp.GetAIOwner());
	if (caiController)
	{
		AForester* forester = Cast<AForester>(caiController->GetPawn());
		if (forester)
		{
			if (forester->ForestResource.IsValid())
			{
				FTreeInstance TreeToCut = forester->ForestResource->GetNearestTreeToCut(forester->GetActorLocation());
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(NearestTreeToCutID.SelectedKeyName, TreeToCut.ID);
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(NearestTreeToCutSpot.SelectedKeyName, TreeToCut.Location);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}

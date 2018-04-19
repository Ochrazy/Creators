// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "ForesterBTTaskCutTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "CollectorAIController.h"
#include "Forester.h"
#include "ForestResource.h"

UForesterBTTaskCutTree::UForesterBTTaskCutTree(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Cut Tree";

	// accept only actors and vectors
	NearestTreeToCut.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UForesterBTTaskCutTree, NearestTreeToCut));
}

void UForesterBTTaskCutTree::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (BBAsset)
	{
		NearestTreeToCut.ResolveSelectedKey(*BBAsset);
	}
	else
	{
		UE_LOG(LogBehaviorTree, Warning, TEXT("Can't initialize task: %s, make sure that behavior tree specifies blackboard asset!"), *GetName());
	}
}

EBTNodeResult::Type UForesterBTTaskCutTree::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACollectorAIController* caiController = Cast<ACollectorAIController>(OwnerComp.GetAIOwner());
	if (caiController)
	{
		AForester* forester = Cast<AForester>(caiController->GetPawn());
		if (forester)
		{			
			int TreeToCutID = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Int>(NearestTreeToCut.GetSelectedKeyID());
			if(forester->ForestResource.IsValid())
				forester->ForestResource->RemoveTree(TreeToCutID);
			
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

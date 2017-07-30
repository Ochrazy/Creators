// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "CollectorBTTaskRetrieveResources.h"
#include "MiningResource.h"
#include "CollectorAIController.h"
#include "Collector.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

UCollectorBTTaskRetrieveResources::UCollectorBTTaskRetrieveResources(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Retrieve Resources";

	// accept only actors and vectors
	NearestMiningSpot.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UCollectorBTTaskRetrieveResources, NearestMiningSpot), AMiningResource::StaticClass());
	bMinerFullInventory.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UCollectorBTTaskRetrieveResources, bMinerFullInventory));
}

void UCollectorBTTaskRetrieveResources::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (BBAsset)
	{
		NearestMiningSpot.ResolveSelectedKey(*BBAsset);
		bMinerFullInventory.ResolveSelectedKey(*BBAsset);
	}
	else
	{
		UE_LOG(LogBehaviorTree, Warning, TEXT("Can't initialize task: %s, make sure that behavior tree specifies blackboard asset!"), *GetName());
	}
}

EBTNodeResult::Type UCollectorBTTaskRetrieveResources::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMiningResource* miningResource = Cast<AMiningResource>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(NearestMiningSpot.GetSelectedKeyID()));
	if (miningResource == nullptr)
		return EBTNodeResult::Failed;
	else
	{
		int amountRetrieved = miningResource->RetrieveResources(50);
		ACollectorAIController* caiController = Cast<ACollectorAIController>(OwnerComp.GetAIOwner());
		if (caiController == nullptr)
			return EBTNodeResult::Failed;
		else
		{
			ACollector* collector = Cast<ACollector>(caiController->GetPawn());
			if (collector == nullptr)
				return EBTNodeResult::Failed;
			else
			{
				collector->AddResources(amountRetrieved);
				if (collector->GetNumResources() > 99)
				{
					OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(bMinerFullInventory.GetSelectedKeyID(), true);
				}

				return EBTNodeResult::Succeeded;
			}
		}
	}
}



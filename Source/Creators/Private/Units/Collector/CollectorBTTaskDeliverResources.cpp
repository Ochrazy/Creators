// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "CollectorBTTaskDeliverResources.h"
#include "CollectorAIController.h"
#include "Collector.h"
#include "CollectorBase.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

UCollectorBTTaskDeliverResources::UCollectorBTTaskDeliverResources(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Deliver Resources";

	// accept only actors and vectors
	bMinerFullInventory.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UCollectorBTTaskDeliverResources, bMinerFullInventory));
}

void UCollectorBTTaskDeliverResources::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (BBAsset)
	{
		bMinerFullInventory.ResolveSelectedKey(*BBAsset);
		Base.ResolveSelectedKey(*BBAsset);
	}
	else
	{
		UE_LOG(LogBehaviorTree, Warning, TEXT("Can't initialize task: %s, make sure that behavior tree specifies blackboard asset!"), *GetName());
	}
}

EBTNodeResult::Type UCollectorBTTaskDeliverResources::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACollectorAIController* caiController = Cast<ACollectorAIController>(OwnerComp.GetAIOwner());
	if (caiController == nullptr)
		return EBTNodeResult::Failed;
	else
	{
		ACollector* collector = Cast<ACollector>(caiController->GetPawn());
		if (collector)
		{
			ACollectorBase* collectorBase = Cast<ACollectorBase>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(Base.GetSelectedKeyID()));
			if (collectorBase == nullptr)
				return EBTNodeResult::Failed;
			else
			{
				int numResources = collector->EmptyResources();
				collectorBase->AddResources(numResources);

				ACreatorsPlayerController* pc = (ACreatorsPlayerController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
				if (pc)
				{
					pc->AddResources(numResources);
				}

				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(bMinerFullInventory.GetSelectedKeyID(), false);
				return EBTNodeResult::Succeeded;
			}
		}
		else return EBTNodeResult::Failed;
	}
}
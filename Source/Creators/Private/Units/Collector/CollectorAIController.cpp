// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "CollectorAIController.h"
#include "CollectorBase.h"
#include "Collector.h"

/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ACollectorAIController::ACollectorAIController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	/* Match with the AI/CollectorBlackboard */
	BaseKeyName = "Base";
}


void ACollectorAIController::Possess(class APawn* inCollector)
{
	Super::Possess(inCollector);

	ACollector* Collector= Cast<ACollector>(inCollector);
	if (Collector)
	{
		if (Collector->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*Collector->BehaviorTree->BlackboardAsset);
		}

		BehaviorComp->StartTree(*Collector->BehaviorTree);
	}
}

void ACollectorAIController::SetNewBase(ACollectorBase* inBase)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(BaseKeyName, inBase);
	}
}





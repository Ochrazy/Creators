// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "CollectorAIController.h"
#include "AICharacter.h"

/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ACollectorAIController::ACollectorAIController(const class FObjectInitializer& ObjectInitializer)
	//: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void ACollectorAIController::Possess(class APawn* inCollector)
{
	Super::Possess(inCollector);

	AAICharacter* aiChar= Cast<AAICharacter>(inCollector);
	if (aiChar)
	{
		if (aiChar->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*aiChar->BehaviorTree->BlackboardAsset);
		}

		BehaviorComp->StartTree(*aiChar->BehaviorTree);
	}
}





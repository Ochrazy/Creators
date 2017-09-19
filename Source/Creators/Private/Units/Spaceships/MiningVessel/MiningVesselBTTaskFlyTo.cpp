// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "MiningVesselBTTaskFlyTo.h"
#include "MiningVessel.h"
#include "AsteroidResource.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

UMiningVesselBTTaskFlyTo::UMiningVesselBTTaskFlyTo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Fly To";
}

void UMiningVesselBTTaskFlyTo::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (BBAsset)
	{
		NearestAsteroid.ResolveSelectedKey(*BBAsset);
	}
	else
	{
		UE_LOG(LogBehaviorTree, Warning, TEXT("Can't initialize task: %s, make sure that behavior tree specifies blackboard asset!"), *GetName());
	}
}

EBTNodeResult::Type UMiningVesselBTTaskFlyTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMiningVessel* MiningVessel = Cast<AMiningVessel>(OwnerComp.GetOwner());
	if (MiningVessel == nullptr)
		return EBTNodeResult::Failed;
	else
	{
		AAsteroidResource* NearestAsteroidResource = Cast<AAsteroidResource>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(NearestAsteroid.GetSelectedKeyID()));
		MiningVessel->SetTarget(NearestAsteroidResource);
	}

	return EBTNodeResult::Succeeded;
}

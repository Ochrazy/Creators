// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "EnvQueryContext_Base.h"
#include "CollectorAIController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "AISystem.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"

void UEnvQueryContext_Base::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	ACollectorAIController* AICon = Cast<ACollectorAIController>((Cast<AActor>((QueryInstance.Owner).Get())->GetInstigatorController()));

	if (AICon && AICon->GetBlackboardComp())
	{
		//Set the context SeeingPawn to the provided context data
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(AICon->GetBlackboardComp()->GetValueAsObject("Base")));
	}
}

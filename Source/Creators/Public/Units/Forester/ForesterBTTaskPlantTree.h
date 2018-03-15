// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ForesterBTTaskPlantTree.generated.h"

/**
 * 
 */
UCLASS()
class CREATORS_API UForesterBTTaskPlantTree : public UBTTaskNode
{
	GENERATED_BODY()
	
	UForesterBTTaskPlantTree(const FObjectInitializer& ObjectInitializer);

	virtual void InitializeFromAsset(UBehaviorTree& Asset);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category = Blackboard)
		struct FBlackboardKeySelector NearestPlantSpot;
	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CollectorAIController.generated.h"

/**
 * 
 */
UCLASS()
class CREATORS_API ACollectorAIController : public AAIController
{
	GENERATED_BODY()

	ACollectorAIController(const class FObjectInitializer& ObjectInitializer);
	
	/* Called whenever the controller possesses a character bot */
	virtual void Possess(class APawn* inCollector) override;

	class UBehaviorTreeComponent* BehaviorComp;

	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName BaseKeyName;
	
public:
	void SetNewBase(class ACollectorBase* inBase);

	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
};
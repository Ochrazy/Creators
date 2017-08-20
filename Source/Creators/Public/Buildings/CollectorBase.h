// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/Building.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "CollectorBase.generated.h"

/**
 * 
 */
UCLASS()
class CREATORS_API ACollectorBase : public ABuilding
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACollectorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACollector> CollectorToSpawnClass;

	void AddResources(int inResources);

	void SpawnCollector();

private:
	int NumResources;

	UPROPERTY(EditDefaultsOnly)
		class UCreatorsBaseWidgetComponent* WidgetComponent;

	UFUNCTION(BlueprintCallable, Category = UI)
		void HandleOnClickedCollectorButton();
};

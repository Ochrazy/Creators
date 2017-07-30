// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/Building.h"
#include "Interfaces/CreatorsInputInterface.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "CollectorBase.generated.h"

/**
 * 
 */
UCLASS()
class CREATORS_API ACollectorBase : public ABuilding, public ICreatorsInputInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACollectorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(Category = Default)
		void OnSelected(ETouchIndex::Type type, UPrimitiveComponent* pComponent);

	/** Static Mesh Comp, Set In BP Default Properties */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = StaticMeshComponents)
		class UStaticMeshComponent* Mesh;

	/* Building To Place*/
	//UPROPERTY(EditDefaultsOnly)
		//TSubclassOf<class ACollector> CollectorToSpawnClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACollector> CollectorToSpawnClass;

	/** receive input: tap */
	virtual void OnInputTap_Implementation() override;

	/** receive input: hold */
	virtual void OnInputHold_Implementation() override;

	/** receive input: hold released */
	virtual void OnInputHoldReleased_Implementation(float DownTime) override;

	/** receive input: swipe update (world space, not screen space)*/
	virtual void OnInputSwipeUpdate_Implementation(const FVector& DeltaPosition) override;

	/** receive input: swipe finished (world space, not screen space) */
	virtual void OnInputSwipeReleased_Implementation(const FVector& DeltaPosition, float DownTime) override;

	void AddResources(int inResources);

	void SpawnCollector();

private:
	int NumResources;

};

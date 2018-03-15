// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/Building.h"
#include "ForesterLodge.generated.h"

/**
 * 
 */
UCLASS()
class CREATORS_API AForesterLodge : public ABuilding
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AForesterLodge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AForester> ForesterToSpawnClass;
	
	void SpawnForester();

	UPROPERTY(EditDefaultsOnly)
		class UCreatorsBaseWidgetComponent* WidgetComponent;

	UFUNCTION(BlueprintCallable, Category = UI)
		void HandleOnClickedForesterButton();
};

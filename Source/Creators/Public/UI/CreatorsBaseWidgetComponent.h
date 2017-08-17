// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Interfaces/CreatorsSelectionInterface.h"
#include "CreatorsBaseWidgetComponent.generated.h"

/**
 * 
 */
UCLASS(config = Game, BlueprintType, HideCategories = Trigger, meta = (BlueprintSpawnableComponent))
class CREATORS_API UCreatorsBaseWidgetComponent : public UWidgetComponent, public ICreatorsSelectionInterface
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	void BeginPlay();

	virtual bool OnSelectionLost_Implementation(const FVector& NewPosition, AActor* NewActor) override;
	virtual bool OnSelectionGained_Implementation() override;

};

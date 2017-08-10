// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetInteractionComponent.h"
#include "CreatorsInteractionComponent.generated.h"

/**
 * 
 */
UCLASS()
class CREATORS_API UCreatorsInteractionComponent : public UWidgetInteractionComponent
{
	GENERATED_BODY()

	UCreatorsInteractionComponent(const FObjectInitializer& ObjectInitializer);
	
public:
	FHitResult PerformCustomTrace() const;
};

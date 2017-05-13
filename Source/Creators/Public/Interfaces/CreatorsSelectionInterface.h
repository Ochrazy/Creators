// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CreatorsSelectionInterface.generated.h"

/** Interface for actors which receive notifies about their selected state */
UINTERFACE()
class UCreatorsSelectionInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICreatorsSelectionInterface
{
	GENERATED_IINTERFACE_BODY()

	/** tries to select actor */
	UFUNCTION(BlueprintNativeEvent)
	bool OnSelectionGained();

	/** tries to deselect actor */
	UFUNCTION(BlueprintNativeEvent)
	bool OnSelectionLost(const FVector& NewPosition, AActor* NewActor);
};

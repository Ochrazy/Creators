// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CreatorsInputInterface.generated.h"

/** Interface for actors which can be selected */
UINTERFACE()
class UCreatorsInputInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICreatorsInputInterface
{
	GENERATED_IINTERFACE_BODY()

	/** receive input: tap */
	UFUNCTION(BlueprintNativeEvent)
	void OnInputTap();

	/** receive input: hold */
	UFUNCTION(BlueprintNativeEvent)
	void OnInputHold();

	/** receive input: hold released */
	UFUNCTION(BlueprintNativeEvent)
	void OnInputHoldReleased(float DownTime);

	/** receive input: swipe update (world space, not screen space)*/
	UFUNCTION(BlueprintNativeEvent)
	void OnInputSwipeUpdate(const FVector& DeltaPosition);

	/** receive input: swipe finished (world space, not screen space) */
	UFUNCTION(BlueprintNativeEvent)
	void OnInputSwipeReleased(const FVector& DeltaPosition, float DownTime);
};

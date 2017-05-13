// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CreatorsTypes.h"
#include "CreatorsSpectatorPawnMovement.generated.h"

UCLASS()
class UCreatorsSpectatorPawnMovement : public USpectatorPawnMovement
{
	GENERATED_UCLASS_BODY()

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	bool bInitialLocationSet;
};


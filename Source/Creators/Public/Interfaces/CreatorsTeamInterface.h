// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CreatorsTeamInterface.generated.h"

/** Interface for actors which can be associated with teams */
UINTERFACE()
class UCreatorsTeamInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICreatorsTeamInterface
{
	GENERATED_IINTERFACE_BODY()

		/** returns the team number of the actor */
		virtual uint8 GetTeamNum() const = 0;
};
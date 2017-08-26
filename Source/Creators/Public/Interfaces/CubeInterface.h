// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeInterface.generated.h"

/** Interface for actors which can be associated with teams */
UINTERFACE()
class UCubeInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICubeInterface
{
	GENERATED_IINTERFACE_BODY()

	/** returns the cube number of the actor */
	virtual uint32 GetCubeNumber() const = 0;
};
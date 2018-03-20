// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resources/BaseResource.h"
#include "InstancedBaseResource.generated.h"

/**
 * 
 */
UCLASS()
class CREATORS_API AInstancedBaseResource : public ABaseResource
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AInstancedBaseResource();
	AInstancedBaseResource(TWeakObjectPtr<UInstancedStaticMeshComponent> inInstancedResource);
	
protected:
	TWeakObjectPtr<UInstancedStaticMeshComponent> InstancedMesh;
};

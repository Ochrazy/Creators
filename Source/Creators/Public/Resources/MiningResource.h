// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseResource.h"
#include "MiningResource.generated.h"

UCLASS()
class CREATORS_API AMiningResource : public ABaseResource
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMiningResource();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnDepleted() override;
};

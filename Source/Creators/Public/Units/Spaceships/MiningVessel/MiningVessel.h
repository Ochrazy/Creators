// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CreatorsBaseActor.h"
#include "MiningVessel.generated.h"

UCLASS()
class CREATORS_API AMiningVessel : public ACreatorsBaseActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMiningVessel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
		float dir;
};
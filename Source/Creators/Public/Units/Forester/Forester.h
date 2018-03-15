// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ForesterLodge.h"
#include "AICharacter.h"
#include "Forester.generated.h"

UCLASS()
class CREATORS_API AForester : public AAICharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AForester();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ATreeResource> TreeToSpawnClass;

private:
	
};

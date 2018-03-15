// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AICharacter.h"
#include "GameFramework/Character.h"
#include "Collector.generated.h"

UCLASS()
class CREATORS_API ACollector : public AAICharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACollector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = Resources)
		void AddResources(int inNumResources);

	UFUNCTION(BlueprintCallable, Category = Resources)
		void EmptyResources();

	UFUNCTION(BlueprintCallable, Category = Resources)
		int GetNumResources();

	//UFUNCTION(BlueprintCallable, Category = Resources)
	//	void DeliverResourcesToBase();

private:
	int NumResources;
	
};

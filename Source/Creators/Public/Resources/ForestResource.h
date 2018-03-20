// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TreeResource.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ForestResource.generated.h"

UCLASS()
class CREATORS_API AForestResource : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AForestResource();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
		ATreeResource* AddTree(const FTransform& inTransform);

	UFUNCTION(BlueprintCallable)
		void RemoveTree(ATreeResource* inTree);

private:
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* Trees;

	TArray<TWeakObjectPtr<ATreeResource>> TreeResources;
	
};

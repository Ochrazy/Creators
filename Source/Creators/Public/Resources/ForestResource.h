// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TreeResource.h"
#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ForestResource.generated.h"

USTRUCT(BlueprintType)
struct FTreeInstance
{
	GENERATED_BODY()

	FTreeInstance()
		: ID(-1), Location(FVector())
	{}

	FTreeInstance(int inID, FVector inLocation)
		: ID(inID), Location(inLocation)
	{
	}

	UPROPERTY(EditAnywhere)
		int ID;

	UPROPERTY(EditAnywhere)
		FVector Location;
};

UCLASS()
class CREATORS_API AForestResource : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AForestResource();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
		void AddTree(const FTransform& inTransform);

	UFUNCTION(BlueprintCallable)
		void RemoveTree(int inTreeID);

	UFUNCTION(BlueprintCallable)
		FTreeInstance GetNearestTreeToCut(const FVector& originLocation) const;

private:
	UPROPERTY(EditAnywhere)
		UInstancedStaticMeshComponent* Trees;

	std::vector<float> age;
	TSet<int> TreesToCut;
	
};

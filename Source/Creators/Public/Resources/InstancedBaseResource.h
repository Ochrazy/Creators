// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resources/BaseResource.h"
#include <vector>
#include "InstancedBaseResource.generated.h"

class UHierarchicalInstancedStaticMeshComponent;

/**
 * 
 */
UCLASS()
class CREATORS_API AInstancedBaseResource : public ABaseResource
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:
	// Sets default values for this actor's properties
	AInstancedBaseResource();

private:
	UPROPERTY(EditAnywhere)
		UHierarchicalInstancedStaticMeshComponent* Trees[4];

	std::vector<float> age;

	int whatToUpdate;
	
	UFUNCTION()
		void timerHandle(int index);
};

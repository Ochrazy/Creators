// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resources/BaseResource.h"
#include "TreeResource.generated.h"

/**
 * 
 */
UCLASS()
class CREATORS_API ATreeResource : public ABaseResource
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATreeResource();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnDepleted() override;

public:
	void Init(UInstancedStaticMeshComponent* inInstancedMesh, int inInstanceID);

private:
	UPROPERTY(VisibleAnywhere)
		float Age;

	TWeakObjectPtr<UInstancedStaticMeshComponent> InstancedForestMesh;

	int InstanceID;
};

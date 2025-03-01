// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interfaces/CreatorsInputInterface.h"
#include "Interfaces/CreatorsSelectionInterface.h"
#include "CreatorsBaseActor.h"
#include "Building.generated.h"

UCLASS()
class CREATORS_API ABuilding : public ACreatorsBaseActor, public ICreatorsInputInterface, public ICreatorsSelectionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void  OnConstruction(const FTransform& Transform) override;

	virtual bool OnSelectionLost_Implementation(const FVector& NewPosition, AActor* NewActor) override;
	virtual bool OnSelectionGained_Implementation() override;

	/** receive input: tap */
	virtual void OnInputTap_Implementation() override;

	/** receive input: hold */
	virtual void OnInputHold_Implementation() override;

	/** receive input: hold released */
	virtual void OnInputHoldReleased_Implementation(float DownTime) override;

	/** receive input: swipe update (world space, not screen space)*/
	virtual void OnInputSwipeUpdate_Implementation(const FVector& DeltaPosition) override;

	/** receive input: swipe finished (world space, not screen space) */
	virtual void OnInputSwipeReleased_Implementation(const FVector& DeltaPosition, float DownTime) override;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* Material;

	TWeakObjectPtr<UMaterialInstanceDynamic> DynMaterial;

};

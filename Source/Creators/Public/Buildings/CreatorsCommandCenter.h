// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/Building.h"
#include "CreatorsCommandCenter.generated.h"

/**
 * 
 */
UCLASS()
class CREATORS_API ACreatorsCommandCenter : public ABuilding
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACreatorsCommandCenter();

	void Tick(float DeltaTime);

	/* Building To Place*/
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ABuilding> BuildingToPlaceClass;
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		class UCreatorsBaseWidgetComponent* WidgetComponent;

	UFUNCTION(BlueprintCallable, Category = UI)
		void EnterBuildingMode();

	TWeakObjectPtr<class ABuilding> BuildingToPlace;

private:
	bool bBuildingMode;
	
};

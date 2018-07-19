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
		TSubclassOf<ABuilding> CollectorClass;

	/* Building To Place*/
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ABuilding> ForesterClass;

	/* Building To Place*/
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ABuilding> BlockClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cube)
		TArray<UStaticMeshComponent*> Blocks;

	virtual void  OnConstruction(const FTransform& Transform) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		class UCreatorsBaseWidgetComponent* WidgetComponent;

	UFUNCTION(BlueprintCallable, Category = UI)
		void LeaveBuildingMode();

	UFUNCTION(BlueprintCallable, Category = UI)
		void EnterBuildingMode(TSubclassOf<ABuilding> buildingClass);

	UFUNCTION(BlueprintCallable, Category = UI)
		void BuildingModeCollector();

	UFUNCTION(BlueprintCallable, Category = UI)
		void BuildingModeForester();

	UFUNCTION(BlueprintCallable, Category = UI)
		void BuildingModeBlock();

	TWeakObjectPtr<ABuilding> BuildingToPlace;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cube)
		class UStaticMeshComponent* CubeBounds;

	UPROPERTY(EditAnywhere, Category = Cube)
		UStaticMesh* BlockAsset;

	UPROPERTY(EditAnywhere, Category = Cube)
		UMaterialInterface* BlockMaterial;

	UPROPERTY(EditAnywhere, Category = Cube)
		UMaterialInterface* BlockMaterial_Overlay;

	UPROPERTY(EditAnywhere, Category = Cube)
		UMaterialInterface* BlockMaterial_Selected;

private:
	enum class BuildingMode { None, Normal, Block } CurrentBuildingMode;

	void NormalBuildingModeTick();
	void BlockBuildingModeTick();
};

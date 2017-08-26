// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "Building.h"


// Sets default values
ABuilding::ABuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
	DynMaterial = UMaterialInstanceDynamic::Create(Material, this);
	//set paramater with Set***ParamaterValue
	DynMaterial->SetVectorParameterValue("Overlay", FLinearColor(1.f, 0.f, 0.f, 0.f));
	Mesh->SetMaterial(0, DynMaterial.Get());
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

uint32 ABuilding::GetCubeNumber() const
{
	return CurrentCubeNumber;
};

void ABuilding::SetCubeNumber(uint32 cubeNumber)
{
	CurrentCubeNumber = cubeNumber;
}

bool ABuilding::OnSelectionLost_Implementation(const FVector& NewPosition, AActor* NewActor)
{
	return true;
}

bool ABuilding::OnSelectionGained_Implementation()
{
	return true;
}

void ABuilding::OnInputTap_Implementation()
{
}

void ABuilding::OnInputHold_Implementation()
{
}

void ABuilding::OnInputHoldReleased_Implementation(float DownTime)
{
}

void ABuilding::OnInputSwipeUpdate_Implementation(const FVector& DeltaPosition)
{
}

void ABuilding::OnInputSwipeReleased_Implementation(const FVector& DeltaPosition, float DownTime)
{
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "CollectorBase.h"
#include "Collector.h"
#include "CreatorsPlayerController.h"
#include "HudWidget.h"

// Sets default values
ACollectorBase::ACollectorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//Mesh->OnInputTouchBegin.AddDynamic(this, &ACollectorBase::OnSelected);
	RootComponent = Mesh;

	NumResources = 0;
}

// Called when the game starts or when spawned
void ACollectorBase::BeginPlay()
{
	Super::BeginPlay();

	DynMaterial = UMaterialInstanceDynamic::Create(Material, this);
	//set paramater with Set***ParamaterValue
	DynMaterial->SetVectorParameterValue("Overlay", FLinearColor(1.f, 0.f, 0.f, 0.f));
	Mesh->SetMaterial(0, DynMaterial.Get());

	ACreatorsPlayerController* pc = (ACreatorsPlayerController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
	const ACreatorsPlayerController* cpController = Cast<ACreatorsPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	HudWidget = (cpController) ? Cast<UHudWidget>(cpController->GetHudWidget()) : NULL;
}

bool ACollectorBase::OnSelectionLost_Implementation(const FVector& NewPosition, AActor* NewActor)
{
	return true;
}

bool ACollectorBase::OnSelectionGained_Implementation()
{
	return true;
}

void ACollectorBase::OnInputTap_Implementation()
{
	HudWidget->ShowBuildingWidget();
}

void ACollectorBase::OnInputHold_Implementation()
{

}

void ACollectorBase::OnInputHoldReleased_Implementation(float DownTime)
{

}

void ACollectorBase::OnInputSwipeUpdate_Implementation(const FVector& DeltaPosition)
{

}

void ACollectorBase::OnInputSwipeReleased_Implementation(const FVector& DeltaPosition, float DownTime)
{

}

void ACollectorBase::AddResources(int inResources)
{
	NumResources += inResources;
}

void ACollectorBase::SpawnCollector()
{
	ACollector* collector;
	collector =  GetWorld()->SpawnActor<ACollector>(CollectorToSpawnClass, GetActorLocation() + FVector(-200.0, 0.0, 0.0), FRotator(0.0, 0.0, 0.0));
	if(collector)
		collector->SetNewBase(this);
}


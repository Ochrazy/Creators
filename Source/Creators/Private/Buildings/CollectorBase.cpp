// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "CollectorBase.h"
#include "Collector.h"
#include "CreatorsPlayerController.h"
#include "BuildingWidget.h"
#include "CreatorsBaseWidgetComponent.h"
#include "WidgetComponent.h"

// Sets default values
ACollectorBase::ACollectorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WidgetComponent = CreateDefaultSubobject<UCreatorsBaseWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	WidgetComponent->SetVisibility(true);

	NumResources = 0;
}

// Called when the game starts or when spawned
void ACollectorBase::BeginPlay()
{
	Super::BeginPlay();

	// Add Delegates
	UBuildingWidget* buildingWidget = Cast<UBuildingWidget>(WidgetComponent->GetUserWidgetObject());
	if(buildingWidget)
		buildingWidget->CollectorButton->OnClicked.AddDynamic(this, &ACollectorBase::HandleOnClickedCollectorButton);
}

void ACollectorBase::HandleOnClickedCollectorButton()
{
	SpawnCollector();
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


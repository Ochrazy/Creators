// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "CollectorBase.h"
#include "Collector.h"
#include "CreatorsPlayerController.h"
#include "BuildingWidget.h"
#include "WidgetComponent.h"

// Sets default values
ACollectorBase::ACollectorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//Mesh->OnInputTouchBegin.AddDynamic(this, &ACollectorBase::OnSelected);
	RootComponent = Mesh;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	WidgetComponent->SetVisibility(true);

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

	if (BuildingWidgetBP)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			//Creating our widget and adding it to our viewport
			BuildingWidget = CreateWidget<UBuildingWidget>(PlayerController, BuildingWidgetBP);
			// Add Delegates
			BuildingWidget->CollectorButton->OnClicked.AddDynamic(this, &ACollectorBase::HandleOnClickedCollectorButton);

			WidgetComponent->SetWidget(BuildingWidget);
			WidgetComponent->SetVisibility(false);
			WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

bool ACollectorBase::OnSelectionLost_Implementation(const FVector& NewPosition, AActor* NewActor)
{
	WidgetComponent->SetVisibility(false);
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	return true;
}

bool ACollectorBase::OnSelectionGained_Implementation()
{
	WidgetComponent->SetVisibility(true);
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	return true;
}

void ACollectorBase::HandleOnClickedCollectorButton()
{
	SpawnCollector();
}

void ACollectorBase::OnInputTap_Implementation()
{
	//HudWidget->ShowBuildingWidget();
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


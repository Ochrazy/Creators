// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "CollectorBase.h"
#include "Collector.h"
#include "CreatorsPlayerController.h"

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
}

void ACollectorBase::OnSelected(ETouchIndex::Type type, UPrimitiveComponent* pComponent)
{
	ACreatorsPlayerController* pc = (ACreatorsPlayerController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
}

void ACollectorBase::OnInputTap_Implementation()
{
	ACreatorsPlayerController* pc = (ACreatorsPlayerController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
	pc->ShowBuildingUI();
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
	//FActorSpawnParameters params;
	//params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ACollector* collector;
	collector =  GetWorld()->SpawnActor<ACollector>(CollectorToSpawnClass, GetActorLocation() + FVector(-200.0, 0.0, 0.0), FRotator());
	if(collector)
		collector->SetNewBase(this);
}


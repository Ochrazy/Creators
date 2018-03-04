// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "Collector.h"
#include "CollectorBase.h"
#include "CollectorAIController.h"


// Sets default values
ACollector::ACollector()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

// Called when the game starts or when spawned
void ACollector::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACollector::AddResources(int inNumResources)
{
	NumResources += inNumResources;
}

int ACollector::EmptyResources()
{
	int emptiedResources = NumResources;
	NumResources = 0;

	return emptiedResources;
}

int ACollector::GetNumResources()
{
	return NumResources;
}

void ACollector::SetNewBase(ACollectorBase* inBase)
{
	ACollectorAIController* AIController = Cast<ACollectorAIController>(GetController());
	if (AIController)
	{
		Base = inBase;
		AIController->SetNewBase(inBase);
	}
}

//void ACollector::DeliverResourcesToBase()
//{
//	ACreatorsPlayerController* pc = (ACreatorsPlayerController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
//	if (pc)
//	{
//		pc->AddResources(NumResources);
//	}
//
//	Base->AddResources(NumResources);
//	NumResources = 0;
//}
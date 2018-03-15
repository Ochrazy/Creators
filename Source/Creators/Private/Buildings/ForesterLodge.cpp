// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "ForesterLodge.h"
#include "CreatorsBaseWidgetComponent.h"
#include "WidgetComponent.h"
#include "ForesterLodgeWidget.h"
#include "Forester.h"
#include "CollectorAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AForesterLodge::AForesterLodge()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WidgetComponent = CreateDefaultSubobject<UCreatorsBaseWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	WidgetComponent->SetVisibility(true);
}

// Called when the game starts or when spawned
void AForesterLodge::BeginPlay()
{
	Super::BeginPlay();

	// Add Delegates
	UForesterLodgeWidget* foresterLodgeWidget = Cast<UForesterLodgeWidget>(WidgetComponent->GetUserWidgetObject());
	if (foresterLodgeWidget)
		foresterLodgeWidget->ForesterButton->OnClicked.AddDynamic(this, &AForesterLodge::HandleOnClickedForesterButton);
}

void AForesterLodge::HandleOnClickedForesterButton()
{
	SpawnForester();
}

void AForesterLodge::SpawnForester()
{
	AForester* forester;
	forester = GetWorld()->SpawnActor<AForester>(ForesterToSpawnClass, GetActorLocation() + FVector(-200.0, 0.0, 0.0), FRotator(0.0, 0.0, 0.0));
	if (forester)
	{
		ACollectorAIController* AIController = Cast<ACollectorAIController>(forester->GetController());
		if (AIController)
		{
			UBlackboardComponent* blackboardComp = AIController->GetBlackboardComp();
			if (blackboardComp)
				blackboardComp->SetValueAsObject("Base", this);
		}
	}
}

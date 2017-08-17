// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "CreatorsBaseWidgetComponent.h"

// Called when the game starts or when spawned
void UCreatorsBaseWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	SetVisibility(false);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

bool UCreatorsBaseWidgetComponent::OnSelectionLost_Implementation(const FVector& NewPosition, AActor* NewActor)
{
	SetVisibility(false);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);

	return true;
}

bool UCreatorsBaseWidgetComponent::OnSelectionGained_Implementation()
{
	SetVisibility(true);
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	return true;
}



// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "WidgetComponent.h"
#include "CreatorsInteractionComponent.h"

UCreatorsInteractionComponent::UCreatorsInteractionComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InteractionDistance = 10000.f;
	InteractionSource = EWidgetInteractionSource::Custom;
	TraceChannel = ECC_Visibility;
	bEnableHitTesting = true;
}

FHitResult UCreatorsInteractionComponent::GetLastRawHitResult() const
{
	return LastRawHitResult;
}

void UCreatorsInteractionComponent::PerformCustomTrace(bool bIgnoreRelatedComponents)
{
	FHitResult HitResult;
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;

	if (bIgnoreRelatedComponents)
	{
		TArray<UPrimitiveComponent*> PrimitiveChildren;
		GetRelatedComponentsToIgnoreInAutomaticHitTesting(PrimitiveChildren);
		Params.AddIgnoredComponents(PrimitiveChildren);
	}

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	ULocalPlayer* LocalPlayer = nullptr;
	if(PlayerController)
		LocalPlayer = PlayerController->GetLocalPlayer();

	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FVector2D MousePosition;
		if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
		{
			FVector WorldOrigin;
			FVector WorldDirection;
			if (UGameplayStatics::DeprojectScreenToWorld(PlayerController, MousePosition, WorldOrigin, WorldDirection) == true)
				GetWorld()->LineTraceSingleByChannel(HitResult, WorldOrigin, WorldOrigin + WorldDirection * InteractionDistance, TraceChannel, Params);
		}
	}

	// Set Last Raw Hit Result before Filtering
	LastRawHitResult = HitResult;

	// Filter Hit Result for Widget Interaction 
	HitResult = FilterWidgetComponents(HitResult);
	SetCustomHitResult(HitResult);
}


FHitResult UCreatorsInteractionComponent::FilterWidgetComponents(const FHitResult& HitResult) const
{
	FHitResult FiteredHitResult;

	// If it's not a custom interaction, we do some custom filtering to ignore invisible widgets.
	if (UWidgetComponent* HitWidgetComponent = Cast<UWidgetComponent>(HitResult.GetComponent()))
	{
		FiteredHitResult = HitResult;
	}

	return FiteredHitResult;
}


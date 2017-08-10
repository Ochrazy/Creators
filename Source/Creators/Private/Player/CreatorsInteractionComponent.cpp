// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "WidgetComponent.h"
#include "CreatorsInteractionComponent.h"

UCreatorsInteractionComponent::UCreatorsInteractionComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InteractionDistance = 10000.f;
	InteractionSource = EWidgetInteractionSource::Custom;
	bEnableHitTesting = true;
}

FHitResult UCreatorsInteractionComponent::PerformCustomTrace() const
{
	FHitResult FinalHitResult;
	TArray<FHitResult> MultiHits;

	TArray<UPrimitiveComponent*> PrimitiveChildren;
	GetRelatedComponentsToIgnoreInAutomaticHitTesting(PrimitiveChildren);

	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredComponents(PrimitiveChildren);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FVector2D MousePosition;
		if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
		{
			FVector WorldOrigin;
			FVector WorldDirection;
			if (UGameplayStatics::DeprojectScreenToWorld(PlayerController, MousePosition, WorldOrigin, WorldDirection) == true)
				GetWorld()->LineTraceMultiByChannel(MultiHits, WorldOrigin, WorldOrigin + WorldDirection * InteractionDistance, TraceChannel, Params);
		}
	}

	// If it's not a custom interaction, we do some custom filtering to ignore invisible widgets.
	for (const FHitResult& HitResult : MultiHits)
	{
		if (UWidgetComponent* HitWidgetComponent = Cast<UWidgetComponent>(HitResult.GetComponent()))
		{
			if (HitWidgetComponent->IsVisible())
				FinalHitResult = HitResult;
		}
		else
		{
			// If we hit something that wasn't a widget component, we're done.
			break;
		}
	}

	return FinalHitResult;
}


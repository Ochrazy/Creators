// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudWidget.generated.h"

/**
 * 
 */
UCLASS()
class CREATORS_API UHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = UI)
		void UpdateResourcesText(int inNumResources);

	UPROPERTY(meta = (BindWidget))
		UGridPanel* BuildPanel;

	UPROPERTY(meta = (BindWidget))
		UButton* CollectorBaseButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* ResourcesText;
};

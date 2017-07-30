// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "UI/HudWidget.h"

void UHudWidget::UpdateResourcesText(int inNumResources)
{
	ResourcesText->SetText(FText::FromString(FString::FromInt(inNumResources)));
}

void UHudWidget::ShowBuildingWidget()
{
	BuildPanel->SetVisibility(ESlateVisibility::Hidden);
	BuildingPanel->SetVisibility(ESlateVisibility::Visible);
}

void UHudWidget::ShowBuildWidget()
{
	BuildPanel->SetVisibility(ESlateVisibility::Visible);
	BuildingPanel->SetVisibility(ESlateVisibility::Hidden);
}

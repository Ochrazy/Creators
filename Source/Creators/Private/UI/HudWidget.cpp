// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "UI/HudWidget.h"

void UHudWidget::UpdateResourcesText(int inNumResources)
{
	ResourcesText->SetText(FText::FromString(FString::FromInt(inNumResources)));
}
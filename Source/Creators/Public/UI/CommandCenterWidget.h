// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommandCenterWidget.generated.h"

/**
 * 
 */
UCLASS()
class CREATORS_API UCommandCenterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		UButton* CollectorBaseButton;
	
};

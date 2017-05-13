// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.


#include "Creators.h"
#include "CreatorsSpectatorPawnMovement.h"
#include "CreatorsCameraComponent.h"
#include "CreatorsSpectatorPawn.h"


UCreatorsSpectatorPawnMovement::UCreatorsSpectatorPawnMovement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bInitialLocationSet(false)
{
	MaxSpeed  = 16000.f;
	Acceleration = 5000.f;
	Deceleration = 4000.f;
}


void UCreatorsSpectatorPawnMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent)
	{
		return;
	}

	ACreatorsPlayerController* PlayerController = Cast<ACreatorsPlayerController>(PawnOwner->GetController());
	if (PlayerController && PlayerController->IsLocalController())
	{
		if (!bInitialLocationSet)
		{
			PawnOwner->SetActorRotation(PlayerController->GetControlRotation());
			PawnOwner->SetActorLocation(PlayerController->GetSpawnLocation());
			bInitialLocationSet = true;
		}

		FVector MyLocation = UpdatedComponent->GetComponentLocation();
		ACreatorsSpectatorPawn* SpectatorPawn = Cast<ACreatorsSpectatorPawn>(PlayerController->GetSpectatorPawn());
		if( ( SpectatorPawn != NULL ) && ( SpectatorPawn->GetCreatorsCameraComponent() != NULL) )
		{
			//SpectatorPawn->GetCreatorsCameraComponent()->ClampCameraLocation(PlayerController, MyLocation);
		}
		UpdatedComponent->SetWorldLocation(MyLocation, false);
	}
}


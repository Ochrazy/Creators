// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.


#include "Creators.h"
#include "CreatorsSpectatorPawn.h"
#include "CreatorsCameraComponent.h"
#include "CreatorsSpectatorPawnMovement.h"

ACreatorsSpectatorPawn::ACreatorsSpectatorPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCreatorsSpectatorPawnMovement>(Super::MovementComponentName))
{
	GetCollisionComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	bAddDefaultMovementBindings = false;
	CreatorsCameraComponent = CreateDefaultSubobject<UCreatorsCameraComponent>(TEXT("CreatorsCameraComponent"));
}

void ACreatorsSpectatorPawn::OnMouseScrollUp()
{
	CreatorsCameraComponent->OnZoomIn();
}

void ACreatorsSpectatorPawn::OnMouseScrollDown()
{
	CreatorsCameraComponent->OnZoomOut();
}


void ACreatorsSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ACreatorsSpectatorPawn::OnMouseScrollUp);
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ACreatorsSpectatorPawn::OnMouseScrollDown);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACreatorsSpectatorPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACreatorsSpectatorPawn::MoveRight);

	PlayerInputComponent->BindAxis("MoveIn", this, &ACreatorsSpectatorPawn::MoveIn);
	PlayerInputComponent->BindAxis("MoveOut", this, &ACreatorsSpectatorPawn::MoveOut);
}


void ACreatorsSpectatorPawn::MoveForward(float Val)
{
	CreatorsCameraComponent->MoveForward( Val );
}


void ACreatorsSpectatorPawn::MoveRight(float Val)
{
	CreatorsCameraComponent->MoveRight( Val );
}

void ACreatorsSpectatorPawn::MoveIn(float Val)
{
	CreatorsCameraComponent->MoveIn(Val);
}

void ACreatorsSpectatorPawn::MoveOut(float Val)
{
	CreatorsCameraComponent->MoveOut(Val);
}

UCreatorsCameraComponent* ACreatorsSpectatorPawn::GetCreatorsCameraComponent()
{
	check( CreatorsCameraComponent != NULL );
	return CreatorsCameraComponent;
}


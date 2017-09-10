// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CreatorsTypes.h"
#include "CreatorsSpectatorPawn.generated.h"

//@TODO: Write a comment here
UCLASS(Blueprintable, BlueprintType)
class ACreatorsSpectatorPawn : public ASpectatorPawn
{
	GENERATED_UCLASS_BODY()

	// Begin ADefaultPawn interface

	/** event call on move forward input */
	virtual void MoveForward(float Val) override;

	/** event call on strafe right input */
	virtual void MoveRight(float Val) override;

	/** Add custom key bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// End ADefaultPawn interface

	// The camera component for this camera
private:
	UPROPERTY(Category = CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCreatorsCameraComponent* CreatorsCameraComponent;
public:

	/** Handles the mouse scrolling down. */
	void OnMouseScrollUp();

	/** Handles the mouse scrolling up. */
	void OnMouseScrollDown();

	void MoveIn(float Val);
	void MoveOut(float Val);
	
	/* Returns a pointer to the Creators camera component the pawn has. */
	UCreatorsCameraComponent* GetCreatorsCameraComponent();
};



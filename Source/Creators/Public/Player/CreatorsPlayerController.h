// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CreatorsTeamInterface.h"
#include "GameFramework/PlayerController.h"
#include "CreatorsPlayerController.generated.h"

class ACreatorsSpectatorPawn;
class UCreatorsCameraComponent;

/**
 * 
 */
UCLASS()
class CREATORS_API ACreatorsPlayerController : public APlayerController, public ICreatorsTeamInterface
{
	GENERATED_BODY()

	ACreatorsPlayerController(const FObjectInitializer& ObjectInitializer);

public:
	// Begin PlayerController interface
	/** fixed rotation */
	virtual void UpdateRotation(float DeltaTime) override;

protected:
	/** update input detection */
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;
	virtual void SetupInputComponent() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);
	// End PlayerController interface

public:

	// Begin CreatorsTeamInterface interface
	virtual uint8 GetTeamNum() const override;
	// End CreatorsTeamInterface interface

	/** set desired camera position. */
	void SetCameraTarget(const FVector& CameraTarget);

	/** helper function to toggle input detection. */
	void SetIgnoreInput(bool bIgnore);

	/** Input handlers. */
	void OnTapPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldReleased(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeStarted(const FVector2D& AnchorPosition, float DownTime);
	void OnSwipeUpdate(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeReleased(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime);
	void OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);

	/** Toggles the ingame menu display. */
	void OnToggleInGameMenu();

	/** Handler for mouse leaving the minimap. */
	void MouseLeftMinimap();

	/** Handler for mouse pressed over minimap. */
	void MousePressedOverMinimap();

	/** Handler for mouse release over minimap. */
	void MouseReleasedOverMinimap();

	UFUNCTION(BlueprintCallable, Category = UI)
		void HandleOnClickedCollectorBaseButton();

	UFUNCTION(BlueprintCallable, Category = UI)
		void HandleOnClickedCollectorButton();

	void AddResources(int inNumResources);
	void EnterBuildingMode();

	class UHudWidget* GetHudWidget() const;

protected:
	/** if set, input and camera updates will be ignored */
	uint8 bIgnoreInput : 1;

	/** currently selected actor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Building)
		TWeakObjectPtr<AActor> SelectedActor;

	/** Swipe anchor. */
	FVector SwipeAnchor3D;

	FVector2D PrevSwipeScreenPosition;

	/** Previous swipe mid point. */
	FVector2D PrevSwipeMidPoint;

	/** Custom input handler. */
	UPROPERTY()
		class UCreatorsInput* InputHandler;

	/**
	* Change current selection (on toggle on the same).
	*
	* @param	NewFocus	Actor to focus on.
	* @param	NewPosition
	*/
	void SetSelectedActor(AActor* NewFocus, const FVector& NewPosition);

	/**
	* Get friendly target under screen space coordinates.
	*
	* @param	ScreenPoint	Screen coordinates to check
	* @param	WorldPoint	Point in the world the screen coordinates projected onto.
	*/
	AActor* GetFriendlyTarget(const FVector2D& ScreenPoint, FVector& WorldPoint) const;

	/**
	* Get audio listener position and orientation.
	*
	* @param
	* @param
	* @param
	*/
	virtual void GetAudioListenerPosition(FVector& Location, FVector& FrontDir, FVector& RightDir) override;

	/* Hud Widget*/
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UHudWidget> HudWidgetBP;

	int NumResources;

	bool bBuildingMode;

	TWeakObjectPtr<class ABuilding> BuildingToPlace;

	/* Building To Place*/
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ABuilding> BuildingToPlaceClass;

	

private:
	/** Helper to return cast version of Spectator pawn. */
	ACreatorsSpectatorPawn* GetCreatorsSpectatorPawn() const;

	/** Helper to return camera component via spectator pawn. */
	UCreatorsCameraComponent* GetCameraComponent() const;

	/** Hud Widget */
	class UHudWidget* HudWidget;
	
};

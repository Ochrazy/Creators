// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Creators.h"
#include "CreatorsHelpers.h"
#include "CreatorsCameraComponent.h"
#include "CreatorsInput.h"
#include "CreatorsSpectatorPawn.h"
#include "CreatorsSelectionInterface.h"
#include "CreatorsInputInterface.h"
#include "CreatorsGameState.h"
#include "CreatorsGameMode.h"
#include "Building.h"
#include "CollectorBase.h"
#include "UI/HudWidget.h"
#include "WidgetComponent.h"
#include "Player/CreatorsInteractionComponent.h"


ACreatorsPlayerController::ACreatorsPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bIgnoreInput(false)
{
//	CheatClass = UCreatorsCheatManager::StaticClass();
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	bHidden = false;
	bShowMouseCursor = true;

	NumResources = 0;

	InteractionComponent = CreateDefaultSubobject<UCreatorsInteractionComponent>(TEXT("InteractionComponent"));
}

void ACreatorsPlayerController::Tick(float DeltaTime)
{
	InteractionComponent->PerformCustomTrace();
}

void ACreatorsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputHandler = NewObject<UCreatorsInput>(this);

	BIND_1P_ACTION(InputHandler, EGameKey::Tap, IE_Pressed, &ACreatorsPlayerController::OnTapPressed);
	BIND_1P_ACTION(InputHandler, EGameKey::Hold, IE_Pressed, &ACreatorsPlayerController::OnHoldPressed);
	BIND_1P_ACTION(InputHandler, EGameKey::Hold, IE_Released, &ACreatorsPlayerController::OnHoldReleased);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Pressed, &ACreatorsPlayerController::OnSwipeStarted);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Repeat, &ACreatorsPlayerController::OnSwipeUpdate);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Released, &ACreatorsPlayerController::OnSwipeReleased);
	//BIND_2P_ACTION(InputHandler, EGameKey::SwipeTwoPoints, IE_Pressed, &ACreatorsPlayerController::OnSwipeTwoPointsStarted);
	//BIND_2P_ACTION(InputHandler, EGameKey::SwipeTwoPoints, IE_Repeat, &ACreatorsPlayerController::OnSwipeTwoPointsUpdate);
	//BIND_2P_ACTION(InputHandler, EGameKey::Pinch, IE_Pressed, &ACreatorsPlayerController::OnPinchStarted);
	//BIND_2P_ACTION(InputHandler, EGameKey::Pinch, IE_Repeat, &ACreatorsPlayerController::OnPinchUpdate);

	FInputActionBinding& ToggleInGameMenuBinding = InputComponent->BindAction("InGameMenu", IE_Pressed, this, &ACreatorsPlayerController::OnToggleInGameMenu);
	ToggleInGameMenuBinding.bExecuteWhenPaused = true;
}

// Called when the game starts or when spawned
void ACreatorsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HudWidgetBP)
	{
		//Creating our widget and adding it to our viewport
		HudWidget = CreateWidget<UHudWidget>(this, HudWidgetBP);
		HudWidget->AddToViewport();
	}
}

UHudWidget* ACreatorsPlayerController::GetHudWidget() const
{
	return HudWidget;
}

void ACreatorsPlayerController::GetAudioListenerPosition(FVector& OutLocation, FVector& OutFrontDir, FVector& OutRightDir)
{
	Super::GetAudioListenerPosition(OutLocation, OutFrontDir, OutRightDir);

	//ACreatorsGameState const* const MyGameState = GetWorld()->GetGameState<ACreatorsGameState>();
	//if (GEngine && GEngine->GameViewport && GEngine->GameViewport->ViewportFrame && MyGameState != NULL /*&& MyGameState->MiniMapCamera.IsValid()*/)
	//{
	//	// Set Listener position to be the center of the viewport, projected into the game world.

	//	FViewport* const Viewport = GEngine->GameViewport->ViewportFrame->GetViewport();
	//	if (Viewport)
	//	{
	//		FVector2D const ScreenRes = Viewport->GetSizeXY();

	//		float GroundLevel = MyGameState->MiniMapCamera->AudioListenerGroundLevel;
	//		const FPlane GroundPlane = FPlane(FVector(0, 0, GroundLevel), FVector::UpVector);
	//		ULocalPlayer* const MyPlayer = Cast<ULocalPlayer>(Player);

	//		// @todo: once PlayerCamera is back in, we can just get the ray origin and dir from that instead of 
	//		// needing to deproject. will be much simpler.
	//		FVector RayOrigin, RayDirection;
	//		FVector2D const ScreenCenterPoint = ScreenRes * 0.5f;
	//		FCreatorsHelpers::DeprojectScreenToWorld(ScreenCenterPoint, MyPlayer, RayOrigin, RayDirection);

	//		FVector const WorldPoint = FCreatorsHelpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);
	//		FVector const AudioListenerOffset = MyGameState->MiniMapCamera->AudioListenerLocationOffset;
	//		OutLocation = WorldPoint.GetClampedToSize(MyGameState->WorldBounds.Min.GetMin(), MyGameState->WorldBounds.Max.GetMax()) + AudioListenerOffset;

	//		bool bUseCustomOrientation = MyGameState->MiniMapCamera->bUseAudioListenerOrientation;
	//		if (bUseCustomOrientation)
	//		{
	//			OutFrontDir = MyGameState->MiniMapCamera->AudioListenerFrontDir;
	//			OutRightDir = MyGameState->MiniMapCamera->AudioListenerRightDir;
	//		}
	//	}
	//}
}

void ACreatorsPlayerController::OnToggleInGameMenu()
{
	/*ACreatorsHUD* const CreatorsHUD = Cast<ACreatorsHUD>(GetHUD());
	if (CreatorsHUD)
	{
		CreatorsHUD->TogglePauseMenu();
	}*/
}

void ACreatorsPlayerController::UpdateRotation(float DeltaTime)
{
	FRotator ViewRotation(0, 0, 0);
	FRotator DeltaRot(0, 0, 0);

	if (PlayerCameraManager)
	{
		PlayerCameraManager->ProcessViewRotation(DeltaTime, ViewRotation, DeltaRot);
	}

	SetControlRotation(ViewRotation);
}

void ACreatorsPlayerController::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	if (!bGamePaused && PlayerInput && InputHandler && !bIgnoreInput)
	{
		InputHandler->UpdateDetection(DeltaTime);
	}

	Super::ProcessPlayerInput(DeltaTime, bGamePaused);

	if (!bIgnoreInput)
	{
		const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
		ACreatorsSpectatorPawn* CreatorsPawn = GetCreatorsSpectatorPawn();
		if ((CreatorsPawn != NULL) && (LocalPlayer != NULL))
		{
			// Create the bounds for the minimap so we can add it as a 'no scroll' zone.
			//ACreatorsHUD* const HUD = Cast<ACreatorsHUD>(GetHUD());
			//ACreatorsGameState const* const MyGameState = GetWorld()->GetGameState<ACreatorsGameState>();
			//if ((MyGameState != NULL) && (MyGameState->MiniMapCamera.IsValid() == true))
			{
				if (LocalPlayer->ViewportClient != NULL)
				{
					//const FIntPoint ViewportSize = LocalPlayer->ViewportClient->Viewport->GetSizeXY();
					//const uint32 ViewTop = FMath::TruncToInt(LocalPlayer->Origin.Y * ViewportSize.Y);
					//const uint32 ViewBottom = ViewTop + FMath::TruncToInt(LocalPlayer->Size.Y * ViewportSize.Y);

					//FVector TopLeft(HUD->MiniMapMargin, ViewBottom - HUD->MiniMapMargin - MyGameState->MiniMapCamera->MiniMapHeight, 0);
					//FVector BottomRight((int32)MyGameState->MiniMapCamera->MiniMapWidth, MyGameState->MiniMapCamera->MiniMapHeight, 0);
					//FBox MiniMapBounds(TopLeft, TopLeft + BottomRight);
					//CreatorsPawn->GetCreatorsCameraComponent()->AddNoScrollZone(MiniMapBounds);
					CreatorsPawn->GetCreatorsCameraComponent()->UpdateCameraMovement(this);
				}
			}
		}
	}
}

void ACreatorsPlayerController::SetCameraTarget(const FVector& CameraTarget)
{
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->SetCameraTarget(CameraTarget);
	}
}

AActor* ACreatorsPlayerController::GetFriendlyTarget(const FVector2D& ScreenPoint, FVector& WorldPoint) const
{
	FHitResult Hit = InteractionComponent->GetLastRawHitResult();

	if (!ACreatorsGameMode::OnEnemyTeam(Hit.GetActor(), this))
	{
		WorldPoint = Hit.ImpactPoint;
		return Hit.GetActor();
	}


	return NULL;
}

void ACreatorsPlayerController::SetIgnoreInput(bool bIgnore)
{
	bIgnoreInput = bIgnore;
}

uint8 ACreatorsPlayerController::GetTeamNum() const
{
	return ECreatorsTeam::Player;
};

void ACreatorsPlayerController::SetSelectedActor(AActor* NewSelectedActor, const FVector& NewPosition)
{
	if (SelectedActor != NewSelectedActor)
	{
		// attempt to unselect current selection
		AActor* const OldSelection = SelectedActor.Get();
		if (OldSelection && OldSelection->GetClass()->ImplementsInterface(UCreatorsSelectionInterface::StaticClass()))
		{
			if (ICreatorsSelectionInterface::Execute_OnSelectionLost(OldSelection, NewPosition, NewSelectedActor))
			{
				// Execute Selection Interface on Components
				auto components = OldSelection->GetComponents();
				for (auto ComponentsIt = components.CreateIterator(); ComponentsIt; ++ComponentsIt)
					if ((*ComponentsIt)->GetClass()->ImplementsInterface(UCreatorsSelectionInterface::StaticClass()))
						ICreatorsSelectionInterface::Execute_OnSelectionLost((*ComponentsIt), NewPosition, NewSelectedActor);

				SelectedActor = NULL;				
			}
		}

		if (!SelectedActor.IsValid())
		{
			// attempt to select new selection
			if (NewSelectedActor && NewSelectedActor->GetClass()->ImplementsInterface(UCreatorsSelectionInterface::StaticClass()))
			{
				if (ICreatorsSelectionInterface::Execute_OnSelectionGained(NewSelectedActor))
				{
					// Execute Selection Interface on Components
					auto components = NewSelectedActor->GetComponents();
					for (auto ComponentsIt = components.CreateIterator(); ComponentsIt; ++ComponentsIt)
						if ((*ComponentsIt)->GetClass()->ImplementsInterface(UCreatorsSelectionInterface::StaticClass()))
							ICreatorsSelectionInterface::Execute_OnSelectionGained((*ComponentsIt));

					SelectedActor = NewSelectedActor;
				}
			}
		}
	}
}

void ACreatorsPlayerController::OnTapPressed(const FVector2D& ScreenPosition, float DownTime)
{
	InteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
	InteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);

	FVector WorldPosition(0.f);
	AActor* const HitActor = GetFriendlyTarget(ScreenPosition, WorldPosition);

	SetSelectedActor(HitActor, WorldPosition);

	InteractionComponent->PerformCustomTrace();
	if (HitActor && HitActor->GetClass()->ImplementsInterface(UCreatorsInputInterface::StaticClass()))
	{
		ICreatorsInputInterface::Execute_OnInputTap(HitActor);
	}
}

void ACreatorsPlayerController::OnHoldPressed(const FVector2D& ScreenPosition, float DownTime)
{
	FVector WorldPosition(0.0f);
	AActor* const HitActor = GetFriendlyTarget(ScreenPosition, WorldPosition);

	SetSelectedActor(HitActor, WorldPosition);

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UCreatorsInputInterface::StaticClass()))
	{
		ICreatorsInputInterface::Execute_OnInputHold(HitActor);
	}
}

void ACreatorsPlayerController::OnHoldReleased(const FVector2D& ScreenPosition, float DownTime)
{
	AActor* const Selected = SelectedActor.Get();
	if (Selected && Selected->GetClass()->ImplementsInterface(UCreatorsInputInterface::StaticClass()))
	{
		ICreatorsInputInterface::Execute_OnInputHoldReleased(Selected, DownTime);
	}
}

void ACreatorsPlayerController::OnSwipeStarted(const FVector2D& AnchorPosition, float DownTime)
{
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->OnSwipeStarted(AnchorPosition);
	}

	FVector WorldPosition(0.0f);
	AActor* const HitActor = GetFriendlyTarget(AnchorPosition, WorldPosition);

	SetSelectedActor(HitActor, WorldPosition);

	/** Get our position in 3d space */
	if (SelectedActor.IsValid())
	{
		SwipeAnchor3D = SelectedActor->GetActorLocation();
	}

	PrevSwipeScreenPosition = AnchorPosition;
}

void ACreatorsPlayerController::OnSwipeUpdate(const FVector2D& ScreenPosition, float DownTime)
{
	AActor* const Selected = SelectedActor.Get();
	if (Selected && Selected->GetClass()->ImplementsInterface(UCreatorsInputInterface::StaticClass()))
	{
		ULocalPlayer* const MyPlayer = Cast<ULocalPlayer>(Player);
		const FPlane GroundPlane = FPlane(FVector(0, 0, SelectedActor->GetActorLocation().Z), FVector(0, 0, 1));

		FVector RayOrigin, RayDirection;
		FCreatorsHelpers::DeprojectScreenToWorld(ScreenPosition, MyPlayer, RayOrigin, RayDirection);
		const FVector ScreenPosition3D = FCreatorsHelpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);

		ICreatorsInputInterface::Execute_OnInputSwipeUpdate(Selected, ScreenPosition3D - SwipeAnchor3D);
	}
	else
	{
		if (GetCameraComponent() != NULL)
		{
			GetCameraComponent()->OnSwipeUpdate(ScreenPosition);
		}
	}

	PrevSwipeScreenPosition = ScreenPosition;
}

void ACreatorsPlayerController::OnSwipeReleased(const FVector2D& ScreenPosition, float DownTime)
{
	AActor* const Selected = SelectedActor.Get();
	if (Selected && Selected->GetClass()->ImplementsInterface(UCreatorsInputInterface::StaticClass()))
	{
		ULocalPlayer* const MyPlayer = Cast<ULocalPlayer>(this->Player);
		const FPlane GroundPlane = FPlane(FVector(0, 0, SelectedActor->GetActorLocation().Z), FVector(0, 0, 1));

		FVector RayOrigin, RayDirection;
		FCreatorsHelpers::DeprojectScreenToWorld(ScreenPosition, MyPlayer, RayOrigin, RayDirection);
		const FVector ScreenPosition3D = FCreatorsHelpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);

		ICreatorsInputInterface::Execute_OnInputSwipeReleased(Selected, ScreenPosition3D - SwipeAnchor3D, DownTime);
	}
	else
	{
		if (GetCameraComponent() != NULL)
		{
			GetCameraComponent()->OnSwipeReleased(ScreenPosition);
		}
	}
}

void ACreatorsPlayerController::OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	PrevSwipeMidPoint = (ScreenPosition1 + ScreenPosition2) * 0.5f;
}

void ACreatorsPlayerController::OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	const FVector2D SwipeMidPoint = (ScreenPosition1 + ScreenPosition2) * 0.5f;
	const FVector MoveDir = FVector(SwipeMidPoint - PrevSwipeMidPoint, 0.0f).GetSafeNormal();
	const float SwipeSpeed = 10000.0f;

	const FRotationMatrix R(PlayerCameraManager->GetCameraRotation() + FRotator(0.0, 90.0, 0.0));
	const FVector WorldSpaceAccel = R.TransformVector(MoveDir) * SwipeSpeed;
	if (GetSpectatorPawn())
	{
		GetSpectatorPawn()->AddMovementInput(WorldSpaceAccel, 1.f);
	}

	PrevSwipeMidPoint = SwipeMidPoint;
}

void ACreatorsPlayerController::OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime)
{
	// Pass the pinch through to the camera component.
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->OnPinchStarted(AnchorPosition1, AnchorPosition2, DownTime);
	}
}

void ACreatorsPlayerController::OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	// Pass the pinch through to the camera component.
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->OnPinchUpdate(InputHandler, ScreenPosition1, ScreenPosition2, DownTime);
	}
}

ACreatorsSpectatorPawn* ACreatorsPlayerController::GetCreatorsSpectatorPawn() const
{
	return Cast<ACreatorsSpectatorPawn>(GetSpectatorPawn());
}

UCreatorsCameraComponent* ACreatorsPlayerController::GetCameraComponent() const
{
	UCreatorsCameraComponent* CameraComponent = NULL;
	if (GetCreatorsSpectatorPawn() != NULL)
	{
		CameraComponent = GetCreatorsSpectatorPawn()->GetCreatorsCameraComponent();
	}
	return CameraComponent;
}

void ACreatorsPlayerController::MouseLeftMinimap()
{
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->EndSwipeNow();
	}
}
void ACreatorsPlayerController::MousePressedOverMinimap()
{
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->EndSwipeNow();
	}
}

void ACreatorsPlayerController::MouseReleasedOverMinimap()
{
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->EndSwipeNow();
	}
}

void ACreatorsPlayerController::AddResources(int inNumResources)
{
	NumResources += inNumResources;

	HudWidget->UpdateResourcesText(NumResources);
}
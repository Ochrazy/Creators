// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Creators.h"
//#include "CreatorsBuilding.h"
#include "CreatorsSpectatorPawn.h"
#include "CreatorsGameMode.h"
#include "CreatorsGameState.h"


ACreatorsGameMode::ACreatorsGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = ACreatorsPlayerController::StaticClass();
	SpectatorClass = ACreatorsSpectatorPawn::StaticClass();
	DefaultPawnClass = ACreatorsSpectatorPawn::StaticClass();
	GameStateClass = ACreatorsGameState::StaticClass();
	//HUDClass = ACreatorsHUD::StaticClass();

	/*static ConstructorHelpers::FClassFinder<ACreatorsBuilding> EmptyWallSlotHelper(TEXT("/Game/Buildings/Wall/Wall_EmptySlot"));
	EmptyWallSlotClass = EmptyWallSlotHelper.Class;
	if ((GEngine != nullptr) && (GEngine->GameViewport != nullptr))
	{
		GEngine->GameViewport->SetSuppressTransitionMessage(true);
	}*/
}

// internal
EGameplayState::Type ACreatorsGameMode::GetGameplayState() const
{
	return GetGameState<ACreatorsGameState>()->GameplayState;
}

const FString ACreatorsGameMode::DifficultyOptionName(TEXT("Difficulty"));


void ACreatorsGameMode::InitGameState()
{
	Super::InitGameState();

	ACreatorsGameState* const CreatorsGameState = GetGameState<ACreatorsGameState>();
	if (CreatorsGameState)
	{
		EGameDifficulty::Type const NewDifficulty = (EGameDifficulty::Type) UGameplayStatics::GetIntOption(OptionsString, DifficultyOptionName, 0);
		CreatorsGameState->SetGameDifficulty(NewDifficulty);

		// start the game!
		CreatorsGameState->StartGameplayStateMachine();
	}
}

void ACreatorsGameMode::RestartPlayer(AController* NewPlayer)
{
	AActor* const StartSpot = FindPlayerStart(NewPlayer);
	if (StartSpot != nullptr)
	{
		// initialize and start it up
		InitStartSpot(StartSpot, NewPlayer);

		ACreatorsPlayerController* const NewPC = Cast<ACreatorsPlayerController>(NewPlayer);
		if (NewPC != nullptr)
		{
			NewPC->SetInitialLocationAndRotation(StartSpot->GetActorLocation(), StartSpot->GetActorRotation());
		}
	}
	else
	{
		UE_LOG(LogGame, Warning, TEXT("Player start not found, failed to restart player"));
	}
}

void ACreatorsGameMode::FinishGame(ECreatorsTeam::Type InWinningTeam)
{
	ACreatorsGameState* CurrentGameState = GetGameState<ACreatorsGameState>();
	// If the game state is valid and we are still playing
	if ((CurrentGameState != nullptr) && (CurrentGameState->GameplayState != EGameplayState::Finished) )
	{
		// tell the gamestate to wrap it up
		CurrentGameState->FinishGame(InWinningTeam);

	}
	// Add a timer to return to main if one does not already exist.
	if (GetWorldTimerManager().GetTimerRate(TimerHandle_ReturnToMenu) == -1.0f )
	{
		// set timer to return to the main menu
		GetWorldTimerManager().SetTimer(TimerHandle_ReturnToMenu, this, &ACreatorsGameMode::ReturnToMenu, TimeBeforeReturnToMenu, false);
	}
}

void ACreatorsGameMode::ReturnToMenu()
{
	GetWorld()->ServerTravel(FString("/Game/Maps/CreatorsMenu"));
}


void ACreatorsGameMode::ExitGame()
{
	ACreatorsPlayerController* PlayerController = nullptr;
	if (GEngine)
	{
		PlayerController = Cast<ACreatorsPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
		PlayerController->ConsoleCommand(TEXT("quit"));
	}
}






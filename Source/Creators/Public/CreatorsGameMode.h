// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CreatorsTypes.h"
#include "GameFramework/GameModeBase.h"
#include "CreatorsGameMode.generated.h"

class AController;
class ACreatorsBuilding;
class SCreatorsTitle;

UCLASS(config=Game)
class ACreatorsGameMode : public AGameModeBase
{
	GENERATED_UCLASS_BODY()

	/** Class for empty wall slot. */
//	UPROPERTY()
//	TSubclassOf<ACreatorsBuilding> EmptyWallSlotClass;

	/** Time before game returns to menu after finish. */
	UPROPERTY(config)
	int32 TimeBeforeReturnToMenu;

	/** Name of the difficulty param on the URL options string. */
	static const FString DifficultyOptionName;
	
	// Begin GameMode interface

	/** Initialize the GameState actor. */
	virtual void InitGameState() override;

	/** 
	 * Handle new player, skips pawn spawning. 
	 * @param NewPlayer	
	 */
	virtual void RestartPlayer(AController* NewPlayer) override;

	// End GameMode interface

	/** 
	 * Finish the game with selected team as winner.
	 *
	 * @param	InWinningTeam		The team that has won.
	 */
	UFUNCTION(BlueprintCallable, Category=Game)
	void FinishGame(ECreatorsTeam::Type InWinningTeam);

	void ReturnToMenu();

	/** Helper method for UI, to exit game. */
	void ExitGame();

	/** Pointer to title text widget. */
	TSharedPtr<SCreatorsTitle> CreatorsTitle;

protected:
	/* Helper to return the current gameplay state. */
	EGameplayState::Type GetGameplayState() const;

	/** Handle for efficient management of UpdateHealth timer */
	FTimerHandle TimerHandle_ReturnToMenu;
};



// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CreatorsTypes.h"
//#include "CreatorsMiniMapCapture.h"
#include "GameFramework/GameStateBase.h"
#include "CreatorsGameState.generated.h"

class ACreatorsChar;
/*class ACreatorsMiniMapCapture;*/

UCLASS(config=Game)
class ACreatorsGameState : public AGameStateBase
{
	GENERATED_UCLASS_BODY()

public:
//	/** Mini map camera component. */
//	TWeakObjectPtr<ACreatorsMiniMapCapture> MiniMapCamera;

	/** Game state. */
	EGameplayState::Type GameplayState;

	/** World bounds for mini map & camera movement. */
	FBox WorldBounds;

	/** Warm up time before game starts */
	UPROPERTY(config)
	int32 WarmupTime;

	/** Current difficulty level of the game. */
	EGameDifficulty::Type GameDifficulty;

	/*
	 * Return number of living pawns from a team. 
	 *
	 * @param InTeam 	The team to get living pawn count for.
	 * @returns 		The living pawn count for the given team.
	 */
	UFUNCTION(BlueprintCallable, Category=Game)
	int32 GetNumberOfLivePawns(TEnumAsByte<ECreatorsTeam::Type> InTeam) const;

	/** 
	 * Set the pause state of the game.
	 * 
	 * @param	bIsPaused	The required pause state
	 */
	UFUNCTION(BlueprintCallable, Category=Game)
	void SetGamePaused(bool bIsPaused);

	/** 
	 * Notification that a character has died. 
	 * 
	 * @param	InChar	The character that has died.
	 */
//	void OnCharDied(ACreatorsChar* InChar);

	/** 
	 * Notification that a character has spawned.
	 * 
	 * @param	InChar	The character that has died.
	 */
//	void OnCharSpawned(ACreatorsChar* InChar);

	
	/** 
	 * Get a team's data. 
	 * 
	 * @param	TeamNum	The team to get the data for
	 * @returns FPlayerData pointer to the data for requested team.
	 */
	FPlayerData* GetPlayerData(uint8 TeamNum) const;

	/** 
	 * Initialize the game-play state machine. 
	 */
	void StartGameplayStateMachine();

	/** 
	 * Change game state and notify observers.
	 * @param	NewState	The required game state.
	 */
	void SetGameplayState(EGameplayState::Type NewState);

	/** Is game currently in state: playing ? */
	bool IsGameActive() const;

	/** Notification that game has started. */
	void OnGameStart();

	/** 
	 * Finish the game.
	 * @param	InWinningTeam	The team that won.
	 */
	void FinishGame(ECreatorsTeam::Type InWinningTeam);

	/** Get time until game starts, in seconds. */
	float GetRemainingWaitTime() const;

	/** Get winning team */
	ECreatorsTeam::Type GetWinningTeam() const;

	/** Get time when game finished */
	float GetGameFinishedTime() const;

	/** 
	 * Set current difficulty level of the game. 
	 *
	 * @param	NewDifficulty	The required game difficulty.
	 */
	void SetGameDifficulty(EGameDifficulty::Type NewDifficulty);

protected:
	
	// @todo, get rid of mutable?
	/** Gameplay information about each player. */	
	mutable TArray<FPlayerData> PlayersData;

	/** Count of live pawns for each team */
	uint32 LivePawnCounter[ECreatorsTeam::MAX];

	/** Team that won.  Set at end of game. */
	ECreatorsTeam::Type WinningTeam;

	/** Time in seconds when the game finished. Set at the end of game. */
	float GameFinishedTime;

	/** Handle for efficient management of UpdateHealth timer */
	FTimerHandle TimerHandle_OnGameStart;

	/** 
	 * Register new char to get information from it.
	 * 
	 * @param	InChar		The character to register.
	 */
	void AddChar(ACreatorsChar* InChar);

	/** 
	 * Unregister char after death.
	 * 
	 * @param	NewState	The character to remove/unregister.
	 */
	void RemoveChar(ACreatorsChar* InChar);

	/** 
	 * Pauses/Unpauses current game timer. 
	 * 
	 * @param	bIsPaused The required pause state.
	 */
	void SetTimersPause(bool bIsPaused);
};



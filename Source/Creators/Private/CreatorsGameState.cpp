// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Creators.h"
//#include "CreatorsBuilding_Brewery.h"
#include "CreatorsGameState.h"
#include "CreatorsTypes.h"

ACreatorsGameState::ACreatorsGameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// team data for: unknown, player, enemy
	PlayersData.AddZeroed(ECreatorsTeam::MAX);
//	MiniMapCamera = nullptr;
	WinningTeam = ECreatorsTeam::Unknown;
	GameFinishedTime = 0;
}

int32 ACreatorsGameState::GetNumberOfLivePawns(TEnumAsByte<ECreatorsTeam::Type> InTeam) const
{
	return LivePawnCounter[InTeam];
}

//void ACreatorsGameState::AddChar(ACreatorsChar* InChar)
//{
//	if (InChar != nullptr)
//	{
//		LivePawnCounter[InChar->GetTeamNum()]++;
//	}
//}
//
//void ACreatorsGameState::RemoveChar(ACreatorsChar* InChar)
//{
//	if (InChar != nullptr)
//	{
//		LivePawnCounter[InChar->GetTeamNum()]--;
//	}
//}
//
//void ACreatorsGameState::OnCharDied(ACreatorsChar* InChar)
//{
//	if ( InChar && (InChar->GetTeamNum() == ECreatorsTeam::Enemy) )
//	{
//		PlayersData[ECreatorsTeam::Player].ResourcesAvailable += InChar->ResourcesToGather;		
//		RemoveChar(InChar);
//	}
//}


//void ACreatorsGameState::OnCharSpawned(ACreatorsChar* InChar)
//{
//	if ( InChar && !InChar->IsPendingKill() )
//	{
//		AddChar(InChar);
//	}
//}

FPlayerData* ACreatorsGameState::GetPlayerData(uint8 TeamNum) const
{
	if (TeamNum != ECreatorsTeam::Unknown)
	{
		return &PlayersData[TeamNum];
	}

	return nullptr;
}

void ACreatorsGameState::SetGameplayState(EGameplayState::Type NewState)
{
	GameplayState = NewState;

	//// notify the breweries of the state change
	//for (int32 i = 0; i < PlayersData.Num(); i++)
	//{
	//	if (PlayersData[i].Brewery.IsValid())
	//	{
	//		PlayersData[i].Brewery->OnGameplayStateChange(NewState);
	//	}
	//}
}

bool ACreatorsGameState::IsGameActive() const
{
	return GameplayState == EGameplayState::Playing;
}

float ACreatorsGameState::GetRemainingWaitTime() const
{
	if (GameplayState == EGameplayState::Waiting)
	{
		return GetWorldTimerManager().GetTimerRemaining(TimerHandle_OnGameStart);
	}

	return 0.f;
}


ECreatorsTeam::Type ACreatorsGameState::GetWinningTeam() const
{
	return WinningTeam;
}

void ACreatorsGameState::OnGameStart()
{
	SetGameplayState(EGameplayState::Playing);

	WinningTeam = ECreatorsTeam::Unknown;
	GameFinishedTime = 0.0f;
}


void ACreatorsGameState::FinishGame(ECreatorsTeam::Type InWinningTeam)
{
	GetWorldTimerManager().ClearAllTimersForObject(this);

	SetGameplayState(EGameplayState::Finished);
	WinningTeam = InWinningTeam;
	GameFinishedTime = GetWorld()->GetRealTimeSeconds();
}



void ACreatorsGameState::StartGameplayStateMachine()
{
	if (WarmupTime > 0.f)
	{
		SetGameplayState(EGameplayState::Waiting);
		GetWorldTimerManager().SetTimer(TimerHandle_OnGameStart, this, &ACreatorsGameState::OnGameStart, WarmupTime, false);
	}
	else
	{
		OnGameStart();
	}
}

void ACreatorsGameState::SetTimersPause(bool bIsPaused)
{
	if (GameplayState == EGameplayState::Waiting )
	{
		bIsPaused ? GetWorldTimerManager().PauseTimer(TimerHandle_OnGameStart) : GetWorldTimerManager().UnPauseTimer(TimerHandle_OnGameStart);
	}
}
void ACreatorsGameState::SetGamePaused(bool bIsPaused)
{
	ACreatorsPlayerController* const MyPlayer = Cast<ACreatorsPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (MyPlayer != nullptr)
	{
		MyPlayer->SetPause(bIsPaused);
		SetTimersPause(bIsPaused);
	}
}

void ACreatorsGameState::SetGameDifficulty(EGameDifficulty::Type NewDifficulty)
{
	GameDifficulty = NewDifficulty;
}

float ACreatorsGameState::GetGameFinishedTime() const
{
	return GameFinishedTime;
}

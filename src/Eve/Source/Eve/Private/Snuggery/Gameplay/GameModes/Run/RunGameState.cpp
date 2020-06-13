// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/Gameplay/GameModes/Run/RunGameState.h"
#include "Net/UnrealNetwork.h"

void ARunGameState::SetGameStartCountdownTimer(const FTimerHandle& timerHandle)
{
    GameStartCountdownTimer = timerHandle;
}

void ARunGameState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ARunGameState, PlayersFinished);
}

void ARunGameState::PlayerWin_Multicast_Implementation(ARunSnuggeryCharacter* runCharacter, float finishTime)
{
    PlayersFinished.Add(runCharacter);
    PlayerFinishTimings.Emplace(runCharacter, finishTime);

    if (CurrentNumPlayers == GetPlayersFinished().Num())
    {
        GameEndedEvent.Broadcast();
    }
}

void ARunGameState::PlayerWin_Server_Implementation(ARunSnuggeryCharacter* runCharacter)
{
    PlayerWin_Multicast(runCharacter, CurrentTime);
}

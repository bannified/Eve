// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EveCore/EveGameModeBase.h"
#include "EveCore/GameModeState.h"
#include "EvePlayerController.h"
#include "EveCharacter.h"

const TCHAR* AEveGameModeBase::s_DefaultPlayerNameFormat = TEXT(R"(Player_{0})");
const FString AEveGameModeBase::s_DefaultPlayerNameFormatString = FString(AEveGameModeBase::s_DefaultPlayerNameFormat);

AEveGameModeBase::AEveGameModeBase()
{

}

void AEveGameModeBase::MoveToState(AGameModeState* NextState)
{
    AGameModeState* oldState = CurrentState;

    if (CurrentState != nullptr)
    {
        CurrentState->OnStateStop();
        CurrentState->OnStateExit();
    }

    if (NextState != nullptr)
    {
        CurrentState = NextState;

        NextState->OnStateEnter();
        NextState->OnStateStart();
    }

    BP_OnStateChanged(oldState, CurrentState);
}

void AEveGameModeBase::WinGame()
{
    BP_WinGame();
}

void AEveGameModeBase::LoseGame()
{
    BP_LoseGame();
}

void AEveGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    PlayerControllerList.AddUnique(NewPlayer);

    Super::PostLogin(NewPlayer);
    
    int numPlayers = GetNumPlayers();

    const FString& defaultPlayerName = FString::Format(s_DefaultPlayerNameFormat, { numPlayers });

    ChangeName(NewPlayer, defaultPlayerName, true);

}

void AEveGameModeBase::ChangeName(AController* Controller, const FString& NewName, bool bNameChange)
{
    Super::ChangeName(Controller, NewName, bNameChange);

    // Get player state.
}

void AEveGameModeBase::BeginPlay()
{
    Super::BeginPlay();
}

void AEveGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CurrentState != nullptr)
    {
        CurrentState->OnStateTick(DeltaTime);
    }

}

void AEveGameModeBase::RegisterPlayer(APlayerController* playerController)
{
    if (playerController == nullptr)
    {
        return;
    }

    PlayerControllerList.AddUnique(playerController);
}

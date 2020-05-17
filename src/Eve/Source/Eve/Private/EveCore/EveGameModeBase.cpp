// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EveCore/EveGameModeBase.h"
#include "EveCore/GameModeState.h"
#include "EvePlayerController.h"
#include "EveCharacter.h"

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

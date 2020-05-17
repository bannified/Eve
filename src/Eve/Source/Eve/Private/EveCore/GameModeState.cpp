// Fill out your copyright notice in the Description page of Project Settings.


#include "EveCore/GameModeState.h"
#include "EveCore/EveGameModeBase.h"

AGameModeState::AGameModeState()
{
    PrimaryActorTick.bCanEverTick = false;
    SetReplicates(true);
}

AGameModeState::AGameModeState(AEveGameModeBase* GameMode) : AGameModeState()
{
    this->GameMode = GameMode;
}

void AGameModeState::Init()
{

}

void AGameModeState::OnStateEnter()
{
    BP_OnStateEnter();
}

void AGameModeState::OnStateStart()
{
    BP_OnStateStart();
}

void AGameModeState::OnStateTick(const float DeltaTime)
{
    BP_OnStateTick(DeltaTime);
}

void AGameModeState::OnStateStop()
{
    BP_OnStateStop();
}

void AGameModeState::OnStateExit()
{
    BP_OnStateExit();
}

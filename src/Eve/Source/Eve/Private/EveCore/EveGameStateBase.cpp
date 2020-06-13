// Fill out your copyright notice in the Description page of Project Settings.


#include "EveCore/EveGameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "EveCore/EveGameModeBase.h"
#include "Net/UnrealNetwork.h"

void AEveGameStateBase::StartGame_Multicast_Implementation()
{
    GameStartedEvent.Broadcast();
}

void AEveGameStateBase::GameEnd_Server_Implementation()
{
    if (!bHasGameEnded)
    {
        bHasGameEnded = true;
        GameEnd_Multicast();
    }
}

void AEveGameStateBase::GameEnd_Multicast_Implementation()
{
    GameEndedEvent.Broadcast();
}

void AEveGameStateBase::RegisterPlayerState_Server_Implementation(APlayerState* playerState)
{
    UWorld* world = GetWorld();
    AEveGameModeBase* eveGameMode = Cast<AEveGameModeBase>(UGameplayStatics::GetGameMode(world));

    eveGameMode->RegisterPlayerState(playerState);
}

void AEveGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AEveGameStateBase, CurrentTime);
    DOREPLIFETIME(AEveGameStateBase, bHasGameEnded);
    DOREPLIFETIME(AEveGameStateBase, CurrentNumPlayers);
}

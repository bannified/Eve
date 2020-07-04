// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/Gameplay/GameModes/Run/RunGameMode.h"
#include "Snuggery/Gameplay/GameModes/Run/RunLevelInfoObject.h"
#include "Snuggery/Gameplay/GameModes/Run/RunGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Eve/Eve.h"
#include "Snuggery/SnuggeryPlayerController.h"
#include "Snuggery/Gameplay/Utility/StartingZone.h"
#include "Snuggery/Gameplay/Utility/FinishingZone.h"
#include "Snuggery/Gameplay/GameModes/Run/RunPlayerState.h"
#include "Snuggery/Gameplay/GameModes/Run/RunSnuggeryCharacter.h"

ARunGameMode::ARunGameMode()
{
    SupposedNumPlayers = 2;
    CountdownDuration = 3;
}

void ARunGameMode::StartGame()
{
    AStartingZone* startingZone = LevelInfoObject->GetStartingZone();

    startingZone->DeactivateZoneBoundary();

    OnGameStart.Broadcast();

    ARunGameState* gameState = GetGameState<ARunGameState>();
    gameState->StartGame_Multicast();
}

void ARunGameMode::BeginPlay()
{
    Super::BeginPlay();

    const UWorld* world = GetWorld();
    LevelInfoObject = Cast<ARunLevelInfoObject>(UGameplayStatics::GetActorOfClass(world, ALevelInfoObjectBase::StaticClass()));

    if (!LevelInfoObject)
    {
        PRINT_ONSCREEN_WARN("LevelInfoObject not found in level.");
        return;
    }


    LevelInfoObject->GetFinishingZone()->OnPlayerEnterZone.AddDynamic(this, &ARunGameMode::OnPlayerCrossLine);
}

void ARunGameMode::StartGameCountdownForAllPlayers(ARunGameState* runGameState)
{
    for (APlayerController* controller : PlayerControllerList)
    {
        ASnuggeryPlayerController* casted = Cast<ASnuggeryPlayerController>(controller);
        
        if (!casted) continue;

        ARunPlayerState* playerState = casted->GetPlayerState<ARunPlayerState>();
        playerState->StartGameCountdown_Client(runGameState->GetCurrentTime() + CountdownDuration);
    }

    GetWorld()->GetTimerManager().SetTimer(m_CountdownTimerHandle, this, &ARunGameMode::StartGame, CountdownDuration, false);
}

void ARunGameMode::PlayerWin(ARunSnuggeryCharacter* runCharacter)
{
    ARunGameState* gameState = GetGameState<ARunGameState>();
    checkf(gameState, 
           TEXT("Invalid gamestate! Set the correct GameState Class in World Settings? The correct class should be %s"), 
           *ARunGameState::StaticClass()->GetFName().ToString());

    gameState->PlayerWin_Server(runCharacter);
}

void ARunGameMode::OnPlayerCrossLine(ASnuggeryCharacter* snuggeryCharacter)
{
    ARunSnuggeryCharacter* runCharacter = Cast<ARunSnuggeryCharacter>(snuggeryCharacter);

    PlayerWin(runCharacter);
}

void ARunGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

}

void ARunGameMode::OnPlayerFullyInitialized(APlayerState* playerState)
{
    Super::OnPlayerFullyInitialized(playerState);

    if (SupposedNumPlayers == InitializedPlayerStates.Num())
    {
        GetWorld()->GetTimerManager().SetTimer(m_CountdownTimerHandle, this, &ARunGameMode::StartGame, CountdownDuration, false);

        ARunGameState* gameState = GetGameState<ARunGameState>();

        if (gameState)
        {
            gameState->SetGameStartCountdownTimer(m_CountdownTimerHandle);
            StartGameCountdownForAllPlayers(gameState);
        }
    }
}

void ARunGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/Gameplay/GameModes/Run/RunHUD.h"
#include "Snuggery/Widgets/GameStartWidget.h"
#include "Snuggery/Widgets/ScoreboardWidget.h"
#include "Snuggery/Gameplay/GameModes/Run/RunGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Snuggery/SnuggeryCharacter.h"
#include "Snuggery/Gameplay/GameModes/Run/RunSnuggeryCharacter.h"

void ARunHUD::OnPlayerStateInitialized()
{
    const UWorld* world = GetWorld();
    ARunGameState* runGameState = Cast<ARunGameState>(UGameplayStatics::GetGameState(world));

    checkf(runGameState != nullptr, TEXT("Game State is not of type %s. Set an appropriate Game State in World Settings."),
           *ASnuggeryGameState::StaticClass()->GetName());

    runGameState->GameEndedEvent.AddDynamic(this, &ARunHUD::OnGameEnded);
}

void ARunHUD::StartGameStartCountdown(float timeToStartGame)
{
    Super::StartGameStartCountdown(timeToStartGame);

    if (GameStartWidget == nullptr)
    {
        GameStartWidget = CreateWidget<UGameStartWidget>(GetOwningPlayerController(), GameStartWidgetClass, TEXT("Game Start Widget"));
    }

    GameStartWidget->SetTimeToStartGame(timeToStartGame);
    GameStartWidget->AddToViewport(501);
}

void ARunHUD::BeginPlay()
{
    Super::BeginPlay();

    ScoreboardWidget = CreateWidget<UScoreboardWidget>(GetOwningPlayerController(), ScoreboardWidgetClass, TEXT("Scoreboard"));
}

void ARunHUD::OnGameEnded()
{
    const UWorld* world = GetWorld();
    ARunGameState* runGameState = Cast<ARunGameState>(UGameplayStatics::GetGameState(world));

    checkf(runGameState != nullptr, TEXT("Game State is not of type %s. Set an appropriate Game State in World Settings."),
           *ASnuggeryGameState::StaticClass()->GetName());

    TMap<ARunSnuggeryCharacter*, float> playerToTimings = runGameState->GetFinishTimings();

    const TArray<ARunSnuggeryCharacter*> players = runGameState->GetPlayersFinished();
    for (int i = 0; i < players.Num(); i++) 
    {
        const ARunSnuggeryCharacter* player = players[i];
        float timing = *playerToTimings.Find(player);

        FScoreboardCellArgs args;
        //args.Avatar = 
        args.Rank = i + 1;
        args.PlayerName = player->GetPlayerState()->GetPlayerName();
        args.Score = FString::SanitizeFloat(timing);
        ScoreboardWidget->AddScoreboardEntry(args);
    }

    ScoreboardWidget->AddToViewport(500);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/Widgets/GameStartWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Snuggery/SnuggeryGameState.h"
#include "Snuggery/Gameplay/GameModes/Run/RunGameState.h"

void UGameStartWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    const UWorld* world = GetWorld();
    ARunGameState* runGameState = Cast<ARunGameState>(UGameplayStatics::GetGameState(world));

    checkf(runGameState != nullptr, TEXT("Game State is not of type %s. Set an appropriate Game State in World Settings."),
           *ASnuggeryGameState::StaticClass()->GetName());

    runGameState->GameStartedEvent.AddDynamic(this, &UGameStartWidget::OnGameStart);

    OnInitialized();
}

void UGameStartWidget::OnGameStart()
{
    RemoveFromParent();
}

void UGameStartWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    UWorld* world = GetWorld();
    ARunGameState* gameState = Cast<ARunGameState>(UGameplayStatics::GetGameState(world));

    if (gameState)
    {
        TimeLeftToGameStart = TimeToStartGame - gameState->GetCurrentTime();
    }
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/SnuggeryHUD.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"

void ASnuggeryHUD::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* owningController = GetOwningPlayerController();

    PlayerUIWidget = UUserWidget::CreateWidgetInstance(*owningController, PlayerUIClass, FName("PlayerUI"));
    PlayerUIWidget->AddToPlayerScreen(300);

    CharacterSelectionWidget = UUserWidget::CreateWidgetInstance(*owningController, CharacterSelectionClass, FName("CharacterSelection"));
    CharacterSelectionWidget->AddToPlayerScreen(400);
    CharacterSelectionWidget->SetVisibility(ESlateVisibility::Hidden);

}

void ASnuggeryHUD::OnPlayerStateInitialized()
{

}

void ASnuggeryHUD::StartGameStartCountdown(float timeToStartGame)
{
    APlayerController* owningController = GetOwningPlayerController();

}

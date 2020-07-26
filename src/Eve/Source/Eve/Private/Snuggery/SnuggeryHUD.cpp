// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/SnuggeryHUD.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"

void ASnuggeryHUD::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* owningController = GetOwningPlayerController();

    CharacterSelectionWidget = UUserWidget::CreateWidgetInstance(*owningController, CharacterSelectionClass, FName("CharacterSelection"));
    CharacterSelectionWidget->AddToPlayerScreen(400);
    CharacterSelectionWidget->SetVisibility(ESlateVisibility::Hidden);

    if (PlayerUIWidget == nullptr)
    {
        PlayerUIWidget = CreateWidget<USnuggeryPlayerUI>(owningController, PlayerUIClass, FName("PlayerUI"));
        PlayerUIWidget->AddToPlayerScreen(300);
    }

}

void ASnuggeryHUD::OnPlayerStateInitialized()
{
    if (PlayerUIWidget == nullptr)
    {
        APlayerController* owningController = GetOwningPlayerController();

        PlayerUIWidget = CreateWidget<USnuggeryPlayerUI>(owningController, PlayerUIClass, FName("PlayerUI"));
        PlayerUIWidget->AddToPlayerScreen(300);
    }

    PlayerUIWidget->OnPlayerStateInitialized();
}

void ASnuggeryHUD::StartGameStartCountdown(float timeToStartGame)
{
    APlayerController* owningController = GetOwningPlayerController();

}

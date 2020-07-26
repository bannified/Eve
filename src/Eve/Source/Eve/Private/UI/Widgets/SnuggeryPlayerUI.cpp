// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/SnuggeryPlayerUI.h"
#include "Kismet/GameplayStatics.h"
#include "Snuggery/SnuggeryPlayerState.h"

void USnuggeryPlayerUI::OnPlayerStateInitialized()
{
    APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    ASnuggeryPlayerState* snuggeryPlayerState = playerController->GetPlayerState<ASnuggeryPlayerState>();

    SetPlayerName(snuggeryPlayerState->GetPlayerName());

    snuggeryPlayerState->OnNameChange.AddDynamic(this, &USnuggeryPlayerUI::SetPlayerName);
}

void USnuggeryPlayerUI::NativeOnInitialized()
{
    Super::NativeOnInitialized();


}

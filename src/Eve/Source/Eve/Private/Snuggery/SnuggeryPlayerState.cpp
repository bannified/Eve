// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/SnuggeryPlayerState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerController.h"
#include "Snuggery/SnuggeryHUD.h"
#include "EveCore/EveGameStateBase.h"
#include "Snuggery/Gameplay/GameModes/Run/RunGameState.h"
#include "Snuggery/SnuggeryPlayerController.h"

void ASnuggeryPlayerState::OnNameChange_Multicast_Implementation(const FString& newName)
{
    OnNameChange.Broadcast(newName);
}

void ASnuggeryPlayerState::StartGameCountdown_Client_Implementation(float timeToStartGame)
{
    const UWorld* world = GetWorld();
    //checkf(UKismetSystemLibrary::IsDedicatedServer(this), TEXT("Player State %s (%p) is not a client."), *GetPlayerName(), this);

    APlayerController* playerController = UGameplayStatics::GetPlayerController(world, 0);

    AHUD* hud = playerController->GetHUD();

    // Cast to Snuggery HUD.
    ASnuggeryHUD* snuggeryHud = Cast<ASnuggeryHUD>(hud);

    if (snuggeryHud)
    {
        snuggeryHud->StartGameStartCountdown(timeToStartGame);
    }
}

void ASnuggeryPlayerState::OnFullyInitialized_Client_Implementation()
{
    const UWorld* world = GetWorld();
    APlayerController* playerController = UGameplayStatics::GetPlayerController(world, 0);

    AHUD* hud = playerController->GetHUD();
    ASnuggeryHUD* castedHud = Cast<ASnuggeryHUD>(hud);

    castedHud->OnPlayerStateInitialized();
}

void ASnuggeryPlayerState::BeginPlay()
{
    Super::BeginPlay();

    // Notifies the HUD on the local player that PlayerState is ready for use.
    // Meant for UI elements that require information from PlayerState.
    ENetRole role = GetRemoteRole();

    UWorld* world = GetWorld();
    ENetMode NetMode = world->GetNetMode();
    APlayerController* playerController = UGameplayStatics::GetPlayerController(world, 0);

    if ((NetMode == NM_Client || NetMode == NM_ListenServer) && IsOwnedBy(playerController))
    {
        ASnuggeryPlayerController* casted = Cast<ASnuggeryPlayerController>(playerController);
        casted->RegisterPlayerState_Server();
    }
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/SnuggeryGameMode.h"
#include "Snuggery/SnuggeryGameState.h"
#include "Snuggery/SnuggeryCharacter.h"
#include "Snuggery/SnuggeryPlayerState.h"
#include "Eve/Eve.h"

void ASnuggeryGameMode::ProcessPlayerMessage(ASnuggeryPlayerState* senderState, FString message)
{
    // todo: parsing for commands, emojis, etc.

    BroadcastPlayerChatMessage(senderState, message);
}

void ASnuggeryGameMode::BroadcastPlayerChatMessage(ASnuggeryPlayerState* senderState, const FString& message)
{
    const TArray<APlayerState*> players = GetGameState<ASnuggeryGameState>()->PlayerArray;

    for (const APlayerState* playerState : players) {
        if (playerState == nullptr) {
            // Possibly due to player state being destroyed but not yet cleared from the list.
            continue;
        }

        APawn* pawn = playerState->GetPawn();
        if (pawn == nullptr) {
            PRINT_ONSCREEN_WARN("%s player state does not have a pawn.", *playerState->GetHumanReadableName());
                continue;
        }

        ASnuggeryCharacter* castedCharacter = Cast<ASnuggeryCharacter>(pawn);
        if (castedCharacter == nullptr) {
            PRINT_ONSCREEN_WARN("%s Player is not a subclass of SnuggeryCharacter.", *pawn->GetHumanReadableName());
            continue;
        }

        castedCharacter->ReceiveMessage(senderState, message);
    }

}

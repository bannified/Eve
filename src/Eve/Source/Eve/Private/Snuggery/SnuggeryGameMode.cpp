// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/SnuggeryGameMode.h"
#include "Snuggery/SnuggeryGameState.h"
#include "Snuggery/SnuggeryCharacter.h"
#include "Snuggery/SnuggeryPlayerState.h"
#include "Engine/DataTable.h"
#include "UI/StringToStringRow.h"
#include "Eve/Eve.h"

const wchar_t* ASnuggeryGameMode::s_EmojiStringFormat = TEXT(R"(<img id="{0}"/>)");
const TCHAR ASnuggeryGameMode::s_EmojiDelimiter = ':';

void ASnuggeryGameMode::ProcessPlayerMessage(ASnuggeryPlayerState* senderState, FString message)
{
    // todo: parsing for commands, emojis, etc.
    FString result;
    const int messageLength = message.Len();

    FString transientText;

    result.Reserve(messageLength);
    bool bIsInEmoji = false;
    int lastDelimiterPosition = -1;

    for (int i = 0; i < messageLength; i++) 
    {
        const TCHAR currentCharacter = message[i];
        if (currentCharacter == s_EmojiDelimiter)
        {
            bIsInEmoji = !bIsInEmoji;

            if (!bIsInEmoji)
            {
                int emojiStringLength = i - lastDelimiterPosition;
                if (emojiStringLength > 2)
                {
                    FString emojiString = message.Mid(lastDelimiterPosition + 1, emojiStringLength - 1);
                    if (IsValidEmoji(emojiString))
                    {
                        transientText = FString::Format(s_EmojiStringFormat, { emojiString });
                        result += transientText;
                    }
                    else
                    {
                        result.Append(message.Mid(lastDelimiterPosition, emojiStringLength + 1));
                    }
                }
            }

            lastDelimiterPosition = i;
        }
        else
        {
            if (!bIsInEmoji)
            {
                result += currentCharacter;
            }
        }
    }

    BroadcastPlayerChatMessage(senderState, result);
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

bool ASnuggeryGameMode::IsValidEmoji(FString emojiString)
{
    return EmojiDataTable->GetRowMap().Contains(FName(*emojiString));
}

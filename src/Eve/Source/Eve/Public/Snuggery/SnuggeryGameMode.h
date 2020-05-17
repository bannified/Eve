// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EveCore/EveGameModeBase.h"
#include "SnuggeryGameMode.generated.h"

class ASnuggeryPlayerState;
class UDataTable;

/**
 * 
 */
UCLASS()
class EVE_API ASnuggeryGameMode : public AEveGameModeBase
{
	GENERATED_BODY()

public:
    /* Chat features */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SnuggeryGameMode|Chat")
    UDataTable* EmojiDataTable;

    /**
     * Performs the necessary processing steps (such as parsing) before broadcasting the message 
     * (or its effects in the case of a chat command).
     */
    UFUNCTION(BlueprintCallable, Category = "SnuggeryGameMode|Chat")
    void ProcessPlayerMessage(ASnuggeryPlayerState* senderState, FString message);

    UFUNCTION(BlueprintCallable, Category = "SnuggeryGameMode|Chat")
    void BroadcastPlayerChatMessage(ASnuggeryPlayerState* senderState, const FString& message);

    UFUNCTION(BlueprintCallable, Category = "SnuggeryGameMode|Chat")
    bool IsValidEmoji(FString emojiString);

private:
    static const wchar_t* s_EmojiStringFormat;
    static const TCHAR s_EmojiDelimiter;
};

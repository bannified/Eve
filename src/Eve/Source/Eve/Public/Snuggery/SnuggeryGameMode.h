// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnuggeryGameMode.generated.h"

class ASnuggeryPlayerState;

/**
 * 
 */
UCLASS()
class EVE_API ASnuggeryGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    /**
     * Performs the necessary processing steps (such as parsing) before broadcasting the message 
     * (or its effects in the case of a chat command).
     */
    UFUNCTION(BlueprintCallable, Category = "SnuggeryGameMode|Chat")
    void ProcessPlayerMessage(ASnuggeryPlayerState* senderState, FString message);

    UFUNCTION(BlueprintCallable, Category = "SnuggeryGameMode|Chat")
    void BroadcastPlayerChatMessage(ASnuggeryPlayerState* senderState, const FString& message);

};

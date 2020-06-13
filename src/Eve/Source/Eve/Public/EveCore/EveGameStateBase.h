// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Snuggery/Gameplay/GameplayDelegates.h"
#include "EveGameStateBase.generated.h"

class AEveGameModeBase;
class APlayerState;

/**
 * 
 */
UCLASS()
class EVE_API AEveGameStateBase : public AGameStateBase
{
    GENERATED_BODY()

    friend AEveGameModeBase;

public:
    UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "RunGameState")
    void StartGame_Multicast();

    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "RunGameState")
    void GameEnd_Server();

    UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "RunGameState")
    void GameEnd_Multicast();

    FORCEINLINE float GetCurrentTime() { return CurrentTime; }
    FORCEINLINE bool GetHasGameEnded() { return bHasGameEnded; }

    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "RunGameState")
    void RegisterPlayerState_Server(APlayerState* playerState);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;

    UPROPERTY(Replicated, BlueprintReadWrite, VisibleAnywhere, Category = "RunGameState")
    int CurrentNumPlayers;

protected:
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "EveGameStateBase")
    float CurrentTime;

    UPROPERTY(Replicated, BlueprintReadWrite, VisibleAnywhere, Category = "RunGameState")
    bool bHasGameEnded;

public:
    UPROPERTY(BlueprintAssignable, Category = "RunGameState")
    FGameStartSignature GameStartedEvent;

    UPROPERTY()
    FGameEndSignature GameEndedEvent;
};

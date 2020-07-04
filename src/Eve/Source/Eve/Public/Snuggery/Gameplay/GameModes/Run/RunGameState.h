// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Snuggery/SnuggeryGameState.h"
#include "Snuggery/Gameplay/GameplayDelegates.h"
#include "RunGameState.generated.h"

class ARunSnuggeryCharacter;

/**
 * 
 */
UCLASS()
class EVE_API ARunGameState : public ASnuggeryGameState
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "RunGameState")
    void SetGameStartCountdownTimer(const FTimerHandle& timerHandle);

    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "RunGameState")
    void PlayerWin_Server(ARunSnuggeryCharacter* runCharacter);

    UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "RunGameState")
    void PlayerWin_Multicast(ARunSnuggeryCharacter* runCharacter, float finishTime);

    FORCEINLINE const TArray<ARunSnuggeryCharacter*> GetPlayersFinished() const { return PlayersFinished; }
    FORCEINLINE const TMap<ARunSnuggeryCharacter*, float> GetFinishTimings() const { return PlayerFinishTimings; }

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;

protected:
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "RunGameState")
    FTimerHandle GameStartCountdownTimer;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "RunGameState")
    TMap<ARunSnuggeryCharacter*, float> PlayerFinishTimings;

    UPROPERTY(Replicated, BlueprintReadWrite, VisibleAnywhere, Category = "RunGameState")
    TArray<ARunSnuggeryCharacter*> PlayersFinished;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Snuggery/SnuggeryGameMode.h"
#include "Snuggery/Gameplay/GameplayDelegates.h"
#include "RunGameMode.generated.h"

class ARunLevelInfoObject;
class ASnuggeryCharacter;
class ARunGameState;
class ARunSnuggeryCharacter;

/**
 * 
 */
UCLASS()
class EVE_API ARunGameMode : public ASnuggeryGameMode
{
    GENERATED_BODY()

    ARunGameMode();

protected:
    UFUNCTION(BlueprintCallable, Category = "RunGameMode")
    void StartGame();

    UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly, Category = "RunGameMode")
    ARunLevelInfoObject* LevelInfoObject;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RunGameMode")
    uint8 SupposedNumPlayers;

    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "RunGameMode")
    uint8 CountdownDuration;

    UFUNCTION(BlueprintCallable, Category = "RunGameMode")
    void StartGameCountdownForAllPlayers(ARunGameState* runGameState);

    UFUNCTION()
    void PlayerWin(ARunSnuggeryCharacter* runCharacter);

private:
 
    UFUNCTION(Category = "RunGameMode")
    void OnPlayerCrossLine(ASnuggeryCharacter* snuggeryCharacter);

    UPROPERTY()
    FTimerHandle m_CountdownTimerHandle;

public:
    virtual void PostLogin(APlayerController* NewPlayer) override;

    virtual void OnPlayerFullyInitialized(APlayerState* playerState) override;

    virtual void Tick(float DeltaTime) override;

};

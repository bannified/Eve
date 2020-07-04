// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Snuggery/SnuggeryHUD.h"
#include "RunHUD.generated.h"

class UGameStartWidget;
class UScoreboardWidget;

/**
 * 
 */
UCLASS()
class EVE_API ARunHUD : public ASnuggeryHUD
{
	GENERATED_BODY()

public:

    virtual void OnPlayerStateInitialized() override;

    virtual void StartGameStartCountdown(float timeToStartGame) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GameStartWidget")
    TSubclassOf<UGameStartWidget> GameStartWidgetClass;

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GameStartWidget")
    UGameStartWidget* GameStartWidget;

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GameStartWidget")
    TSubclassOf<UScoreboardWidget> ScoreboardWidgetClass;

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GameStartWidget")
    UScoreboardWidget* ScoreboardWidget;

    UFUNCTION()
    void OnGameEnded();
};

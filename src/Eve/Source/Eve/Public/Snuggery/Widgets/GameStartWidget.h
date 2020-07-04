// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStartWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVE_API UGameStartWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    inline void SetTimeToStartGame(float time) { TimeToStartGame = time; }

    virtual void NativeOnInitialized() override;

    UFUNCTION()
    void OnGameStart();

protected:
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "GameStartWidget")
    float TimeToStartGame;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "GameStartWidget")
    float TimeLeftToGameStart;

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};

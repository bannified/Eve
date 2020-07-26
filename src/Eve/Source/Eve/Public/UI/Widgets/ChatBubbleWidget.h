// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatBubbleWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVE_API UChatBubbleWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "ChatBubbleWidget")
    void ShowWithMessage(const FString& message, float revealDuration);

    UFUNCTION(BlueprintImplementableEvent, Category = "ChatBubbleWidget")
    void ShowWithMessage_Callback(const FString& message);

    UFUNCTION(BlueprintCallable, Category = "ChatBubbleWidget")
    void Hide();

    UFUNCTION(BlueprintImplementableEvent, Category = "ChatBubbleWidget")
    void Hide_Callback();

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ChatBubbleWidget")
    FTimerHandle HideTimerHandle;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ChatBubbleWidget")
    float RevealRate;
};

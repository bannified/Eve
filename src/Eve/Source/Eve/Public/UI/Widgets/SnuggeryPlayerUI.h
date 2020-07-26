// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatboxWidget.h"
#include "SnuggeryPlayerUI.generated.h"

/**
 * 
 */
UCLASS()
class EVE_API USnuggeryPlayerUI : public UUserWidget
{
	GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite, Category = "SnuggeryPlayerUI")
    FString PlayerName;

    UFUNCTION(BlueprintImplementableEvent)
    void SetPlayerName_CallbackEvent(const FString& value);

    UFUNCTION(BlueprintCallable)
    const FString& GetPlayerName() const { return PlayerName; }

    // Change to UUIPROPERTY
    UFUNCTION(BlueprintCallable, Category = "SnuggeryPlayerUI")
    void SetPlayerName(const FString& value) {
        PlayerName = value;
        SetPlayerName_CallbackEvent(PlayerName);
    }

    void OnPlayerStateInitialized();

    FORCEINLINE UChatboxWidget* GetChatboxWidget() { return ChatboxWidget; }

protected:
    virtual void NativeOnInitialized() override;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "SnuggeryPlayerUI")
    UChatboxWidget* ChatboxWidget;
};

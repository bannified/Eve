// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widgets/ChatMessageCellWidget.h"
#include "ChatboxWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVE_API UChatboxWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Chatbox")
    void AddMessageToChatHistoryBox(const FString& sender, const FString& message);

    UFUNCTION(BlueprintImplementableEvent, Category = "Chatbox")
    void OnMessageCellAdd_Callback(const UChatMessageCellWidget* cell);

    UFUNCTION(BlueprintCallable, Category = "Chatbox")
    void ClearChatbox();

    UFUNCTION(BlueprintImplementableEvent, Category = "Chatbox")
    void OnChatboxClear_Callback(UChatMessageCellWidget* cellWidget);

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Chatbox")
    TSubclassOf<UChatMessageCellWidget> ChatMessageCellClass;

    UFUNCTION(BlueprintCallable, Category = "Chatbox")
    void SendMessage(const FString& message);

    UFUNCTION(BlueprintImplementableEvent, Category = "Chatbox")
    void OnSendMessage_Callback();

    UFUNCTION(BlueprintCallable, Category = "Chatbox")
    void SetChatInputFocus();

    UFUNCTION(BlueprintImplementableEvent, Category = "Chatbox")
    void SetChatInputFocus_Callback();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Chatbox")
    TArray<UChatMessageCellWidget*> MessageCellList;
};

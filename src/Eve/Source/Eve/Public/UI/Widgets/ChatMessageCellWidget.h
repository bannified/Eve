// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatMessageCellWidget.generated.h"

USTRUCT(BlueprintType)
struct EVE_API FChatMessageCellArgs {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ChatMessageCell")
    FString Message;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ChatMessageCell")
    FString SenderName;

};

/**
 * 
 */
UCLASS()
class EVE_API UChatMessageCellWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ChatMessageCell")
    FString Message;

public:
    UFUNCTION(BlueprintCallable, Category = "ChatMessageCell")
    void Setup(const FChatMessageCellArgs& args);

    UFUNCTION(BlueprintImplementableEvent)
    void SetMessage_CallbackEvent(const FString& value);

    UFUNCTION(BlueprintCallable)
    const FString& GetMessage() const { return Message; }

    UFUNCTION(BlueprintCallable)
    void SetMessage(const FString& value) {
        Message = value;
        SetMessage_CallbackEvent(Message);
    }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ChatMessageCell")
    FString SenderName;

public:
    UFUNCTION(BlueprintImplementableEvent)
    void SetSenderName_CallbackEvent(const FString& value);

    UFUNCTION(BlueprintCallable)
    const FString& GetSenderName() const { return SenderName; }

    // Change to UUIPROPERTY
    UFUNCTION(BlueprintCallable)
    void SetSenderName(const FString& value) {
        SenderName = value;
        SetSenderName_CallbackEvent(SenderName);
    }

    virtual void NativeOnInitialized() override;
};

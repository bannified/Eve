// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/ChatboxWidget.h"
#include "UI/Widgets/ChatMessageCellWidget.h"
#include "Snuggery/SnuggeryCharacter.h"

void UChatboxWidget::AddMessageToChatHistoryBox(const FString& sender, const FString& message)
{
    UChatMessageCellWidget* cellWidget = CreateWidget<UChatMessageCellWidget>(GetOwningPlayer(), ChatMessageCellClass);
    FChatMessageCellArgs args;
    args.SenderName = sender;
    args.Message = message;
    cellWidget->Setup(args);
    
    MessageCellList.Add(cellWidget);

    OnMessageCellAdd_Callback(cellWidget);
}

void UChatboxWidget::ClearChatbox()
{
    for (UChatMessageCellWidget* cell : MessageCellList)
    {
        cell->RemoveFromParent();
    }

    MessageCellList.Empty();
}

void UChatboxWidget::SendMessage(const FString& message)
{
    ASnuggeryCharacter* owningCharacter = GetOwningPlayerPawn<ASnuggeryCharacter>();
    
    owningCharacter->SendMessage(message);

    OnSendMessage_Callback();
}

void UChatboxWidget::SetChatInputFocus()
{
    SetChatInputFocus_Callback();
}

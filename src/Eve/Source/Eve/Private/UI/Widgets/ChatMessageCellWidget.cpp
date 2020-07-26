// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/ChatMessageCellWidget.h"

void UChatMessageCellWidget::Setup(const FChatMessageCellArgs& args)
{
    SetMessage(args.Message);
    SetSenderName(args.SenderName);
}

void UChatMessageCellWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

}

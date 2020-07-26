// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/ChatBubbleWidget.h"

void UChatBubbleWidget::ShowWithMessage(const FString& message, float revealDuration)
{
    GetWorld()->GetTimerManager().SetTimer(HideTimerHandle, this, &UChatBubbleWidget::Hide, revealDuration, false);

    ShowWithMessage_Callback(message);
}

void UChatBubbleWidget::Hide()
{
    GetWorld()->GetTimerManager().ClearTimer(HideTimerHandle);
    Hide_Callback();
}

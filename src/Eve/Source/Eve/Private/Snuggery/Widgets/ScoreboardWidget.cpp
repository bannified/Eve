// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/Widgets/ScoreboardWidget.h"

void UScoreboardWidget::AddScoreboardEntry(const FScoreboardCellArgs& args)
{
    UScoreboardCellWidget* cellWidget = CreateWidget<UScoreboardCellWidget>(GetOwningPlayer(), ScoreboardCellClass);
    cellWidget->Setup(args);
    BP_OnScoreboardCellAdded(cellWidget);
}

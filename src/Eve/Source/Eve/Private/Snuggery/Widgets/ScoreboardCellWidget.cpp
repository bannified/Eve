// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/Widgets/ScoreboardCellWidget.h"

void UScoreboardCellWidget::Setup(const FScoreboardCellArgs& args)
{
    Rank = args.Rank;
    PlayerName = args.PlayerName;
    Avatar = args.Avatar;
    Score = args.Score;
}

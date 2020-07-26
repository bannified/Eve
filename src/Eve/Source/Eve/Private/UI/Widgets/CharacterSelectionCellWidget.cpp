// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/CharacterSelectionCellWidget.h"

void UCharacterSelectionCellWidget::Setup(const FCharacterSelectionCellArgs& args)
{
    CharacterData = args.CharacterData;
    SetCharacterBrush(args.CharacterData->CharacterSelectionImage);
    SetDisplayName(args.CharacterData->DisplayName);
}

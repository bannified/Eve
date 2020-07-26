// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/CharacterSelectionWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Snuggery/SnuggeryGameState.h"
#include "UI/Widgets/CharacterSelectionCellWidget.h"
#include "Snuggery/SnuggeryCharacter.h"

void UCharacterSelectionWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    ASnuggeryGameState* snuggeryGameState = Cast<ASnuggeryGameState>(UGameplayStatics::GetGameState(GetWorld()));
    TArray<USnuggeryCharacterDataAsset*> characterDatas = snuggeryGameState->GetCharacterDataList();

    for (USnuggeryCharacterDataAsset* entry : characterDatas)
    {
        UCharacterSelectionCellWidget* cell = CreateWidget<UCharacterSelectionCellWidget>(GetOwningPlayer(), CharacterSelectionCellClass);
        FCharacterSelectionCellArgs args;
        args.CharacterData = entry;
        
        cell->Setup(args);
        SelectionCells.Add(cell);
        cell->CharacterDataSelected.AddDynamic(this, &UCharacterSelectionWidget::OnCharacterSelected);

        OnSelectionCellAdded_Callback(cell);
    }
}

void UCharacterSelectionWidget::OnCharacterSelected(USnuggeryCharacterDataAsset* characterData)
{
    ASnuggeryCharacter* snuggeryCharacter = Cast<ASnuggeryCharacter>(GetOwningPlayerPawn());
    snuggeryCharacter->SwitchCharacter_Server(characterData);

    OnCharacterSelected_Callback(characterData);
}

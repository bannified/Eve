// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectionWidget.generated.h"

class UCharacterSelectionCellWidget;
class USnuggeryCharacterDataAsset;

/**
 * 
 */
UCLASS()
class EVE_API UCharacterSelectionWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeOnInitialized() override;

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "CharacterSelectionWidget")
    TSubclassOf<UCharacterSelectionCellWidget> CharacterSelectionCellClass;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CharacterSelectionWidget")
    TArray<UCharacterSelectionCellWidget*> SelectionCells;

    UFUNCTION(BlueprintImplementableEvent, Category = "CharacterSelectionWidget")
    void OnSelectionCellAdded_Callback(UCharacterSelectionCellWidget* cellWidget);

    UFUNCTION(Category = "CharacterSelectionWidgets")
    void OnCharacterSelected(USnuggeryCharacterDataAsset* characterData);

    UFUNCTION(BlueprintImplementableEvent, Category = "CharacterSelectionWidgets")
    void OnCharacterSelected_Callback(USnuggeryCharacterDataAsset* characterData);
};

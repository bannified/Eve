// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateBrush.h"
#include "CharacterSelectionCellWidget.generated.h"

class USnuggeryCharacterDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDataSelectedDelegate, USnuggeryCharacterDataAsset*, characterData);

USTRUCT(BlueprintType)
struct EVE_API FCharacterSelectionCellArgs {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ChatMessageCell")
    USnuggeryCharacterDataAsset* CharacterData;
};

/**
 * 
 */
UCLASS()
class EVE_API UCharacterSelectionCellWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CharacterSelectionCellWidget")
    USnuggeryCharacterDataAsset* CharacterData;

public:
    UFUNCTION(BlueprintCallable, Category = "CharacterSelectionCellWidget")
    void Setup(const FCharacterSelectionCellArgs& args);

    UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "CharacterSelectionCellWidget")
    FCharacterDataSelectedDelegate CharacterDataSelected;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CharacterSelectionCellWidget")
    FSlateBrush CharacterBrush;

    UFUNCTION(BlueprintCallable, Category = "CharacterSelectionCellWidget")
    void SetCharacterBrush(const FSlateBrush& brush) { 
        CharacterBrush = brush;
        SetCharacterBrush_Callback(brush);
    }

    UFUNCTION(BlueprintImplementableEvent, Category = "CharacterSelectionCellWidget")
    void SetCharacterBrush_Callback(const FSlateBrush& brush);

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CharacterSelectionCellWidget")
    FName DisplayName;

    UFUNCTION(BlueprintCallable, Category = "CharacterSelectionCellWidget")
    void SetDisplayName(const FName& name) {
        DisplayName = name;
        SetDisplayName_Callback(name);
    }

    UFUNCTION(BlueprintImplementableEvent, Category = "CharacterSelectionCellWidget")
    void SetDisplayName_Callback(const FName& name);
};

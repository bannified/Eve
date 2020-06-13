// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateBrush.h"
#include "Snuggery/Widgets/ScoreboardCellWidget.h"
#include "ScoreboardWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVE_API UScoreboardWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void AddScoreboardEntry(const FScoreboardCellArgs& args);

protected:
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ScoreboardWidget")
    TSubclassOf<UScoreboardCellWidget> ScoreboardCellClass;

    UFUNCTION(BlueprintImplementableEvent, Category = "ScoreboardWidget")
    void BP_OnScoreboardCellAdded(UScoreboardCellWidget* cellWidget);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreboardCellWidget.generated.h"

USTRUCT(BlueprintType)
struct EVE_API FScoreboardCellArgs 
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "ScoreboardWidget")
    int32 Rank;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "ScoreboardWidget")
    FString PlayerName;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "ScoreboardWidget")
    FSlateBrush Avatar;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "ScoreboardWidget")
    FString Score;
};

/**
 * 
 */
UCLASS()
class EVE_API UScoreboardCellWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void Setup(const FScoreboardCellArgs& args);

protected:
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "ScoreboardWidget")
    int32 Rank;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "ScoreboardWidget")
    FString PlayerName;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "ScoreboardWidget")
    FSlateBrush Avatar;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "ScoreboardWidget")
    FString Score;

};

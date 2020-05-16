// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StringToStringRow.generated.h"

/** Simple struct for rich text styles */
USTRUCT(Blueprintable, BlueprintType)
struct EVE_API FStringToStringRow : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString RichTextTag;
};

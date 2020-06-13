// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "SnuggeryCharacterDataAsset.generated.h"

class ASnuggeryCharacterBase;
class USkeletalMesh;
class UAnimBlueprint;

/**
 * Data asset that contains information about a character setup, from mesh(es), to animations, and material properties.
 */
UCLASS()
class EVE_API USnuggeryCharacterDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Customization")
    FName DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Customization")
    FSlateBrush CharacterSelectionImage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Customization")
    FSlateBrush ChatAvatarImage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Customization")
    USkeletalMesh* SkeletalMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Customization")
    UAnimBlueprint* AnimationBlueprint;

public:
    UFUNCTION(BlueprintCallable, Category = "SnuggeryCharacter")
    virtual void InitializeCharacter(ASnuggeryCharacterBase* character);

    UFUNCTION(BlueprintCallable, Category = "SnuggeryCharacter")
    bool IsValid();

protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter")
    void K2_InitializeCharacter(ASnuggeryCharacterBase* character);

};

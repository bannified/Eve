// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EveCore/EveGameStateBase.h"
#include "Gameplay/GameplayDelegates.h"
#include "SnuggeryGameState.generated.h"

class USnuggeryCharacterDataAsset;

/**
 * 
 */
UCLASS()
class EVE_API ASnuggeryGameState : public AEveGameStateBase
{
	GENERATED_BODY()
	
public:
    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;

    ASnuggeryGameState();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SnuggeryGameState")
    TArray<USnuggeryCharacterDataAsset*> CharacterDataList;
};

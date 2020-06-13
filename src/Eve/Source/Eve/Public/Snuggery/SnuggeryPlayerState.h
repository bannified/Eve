// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SnuggeryPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class EVE_API ASnuggeryPlayerState : public APlayerState
{
	GENERATED_BODY()
	
    void OnNameChange_Multicast();
};

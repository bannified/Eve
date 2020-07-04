// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Snuggery/Gameplay/GameplayDelegates.h"
#include "SnuggeryPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class EVE_API ASnuggeryPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
    UPROPERTY(BlueprintAssignable, Category = "SnuggeryPlayerState")
    FNameChangeSignature OnNameChange;

    UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category = "SnuggeryPlayerState")
    void OnNameChange_Multicast(const FString& newName);

    UFUNCTION(Client, Reliable, Category = "SnuggeryPlayerState")
    void StartGameCountdown_Client(float timeToStartGame);

    UFUNCTION(Client, Reliable, Category = "SnuggeryPlayerState")
    virtual void OnFullyInitialized_Client();

protected:
    virtual void BeginPlay() override;

};

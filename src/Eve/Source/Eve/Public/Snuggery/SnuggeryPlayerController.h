// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SnuggeryPlayerController.generated.h"

class ASnuggeryCharacterBase;
class APlayerState;

/**
 *
 */
UCLASS()
class EVE_API ASnuggeryPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    UPROPERTY(Replicated, VisibleAnywhere, Category = "SnuggeryPlayerController")
    ASnuggeryCharacterBase* SnuggeryCharacter;

protected:

    /* Camera Control */
    virtual void OnTurn(float inScale);

    /* Movement input */
    virtual void OnMoveRightInput(float inScale);
    virtual void OnMoveForwardInput(float inScale);

    /* Look Input */
    virtual void OnLookRightInput(float inScale);
    virtual void OnLookUpInput(float inScale);

    virtual void OnCameraPanStart();
    virtual void OnCameraPanEnd();

    virtual void OnJumpStart();
    virtual void OnJumpEnd();

    /* Begin PlayerController interface */

    virtual void SetupInputComponent() override;

    virtual void OnPossess(APawn* aPawn) override;
    virtual void OnUnPossess() override;

    /* End PlayerController interface */

    virtual void BeginPlay() override;
public:
    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;

    UFUNCTION(Server, Reliable, Category = "SnuggeryPlayerController")
    virtual void RegisterPlayerState_Server();

};

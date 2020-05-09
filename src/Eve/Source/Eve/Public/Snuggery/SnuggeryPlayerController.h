// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SnuggeryPlayerController.generated.h"

class ASnuggeryCharacter;

/**
 *
 */
UCLASS()
class EVE_API ASnuggeryPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    ASnuggeryCharacter* SnuggeryCharacter;

protected:
    /* Movement input */
    virtual void OnMoveRightInput(float inScale);

    virtual void OnMoveForwardInput(float inScale);

    virtual void OnJumpStart();
    virtual void OnJumpEnd();

    /* Begin PlayerController interface */

    virtual void SetupInputComponent() override;

    virtual void OnPossess(APawn* aPawn) override;
    virtual void OnUnPossess() override;

    /* End PlayerController interface */

};

// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EvePlayerController.generated.h"

class AEveCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerControllerInputEvent, AEvePlayerController*, character);

UCLASS()
class AEvePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	AEveCharacter* m_CharacterBase;

public:
	AEvePlayerController();

protected:

	/* Movement Input */

	/* Horizontal movement, along the x-axis */
	virtual void OnMoveRightInput(float inScale);
	/* In-and-out movement, along the y-axis */
	virtual void OnMoveForwardInput(float inScale);
    
    /* Jump input */
    virtual void OnJumpStart();
    virtual void OnJumpEnd();

    /* Look Input */
    virtual void OnLookRightInput(float inScale);
    virtual void OnLookUpInput(float inScale);

	/* Events (for BP) */
	FOnPlayerControllerInputEvent ReceiveMoveRightInput;
	FOnPlayerControllerInputEvent ReceiveMoveForwardInput;


	// Begin PlayerController interface
	virtual void SetupInputComponent() override;
	// End PlayerController interface

    virtual void OnPossess(APawn* aPawn) override;
    virtual void OnUnPossess() override;
};



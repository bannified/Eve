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

	/* Movement */

	/* Horizontal movement, along the x-axis */
	virtual void OnMoveRight(float inScale);

	/* In-and-out movement, along the y-axis */
	virtual void OnMoveForward(float inScale);

	/* Vertical movement, along the z-axis */
	virtual void OnMoveUp(float inScale);

	/* Events (for BP) */
	FOnPlayerControllerInputEvent MoveRight;
	FOnPlayerControllerInputEvent MoveForward;
	FOnPlayerControllerInputEvent MoveUp;


	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
};



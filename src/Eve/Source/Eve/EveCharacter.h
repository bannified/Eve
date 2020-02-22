// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EveCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEveCharacterInputDelegate, AEveCharacter*, character);

class AEvePlayerController;

class UCameraComponent;
class USpringArmComponent;

UCLASS(Blueprintable)
class AEveCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEveCharacter();

	/* Movement */

	/* Horizontal movement, along the x-axis */
	virtual void OnMoveRight(float inScale);

	/* In-and-out movement, along the y-axis */
	virtual void OnMoveForward(float inScale);

    /**
     * Start of Jump input
     */
    virtual void OnJumpStart();

    /**
     * End of Jump input
     */
    virtual void OnJumpEnd();

    /* End Movement */

    UPROPERTY(BlueprintAssignable, Category = "EveCharacter")
    FOnEveCharacterInputDelegate MoveRightEvent;
    UPROPERTY(BlueprintAssignable, Category = "EveCharacter")
    FOnEveCharacterInputDelegate MoveForwardEvent;

    /* Look */
    virtual void OnLookRight(float inScale);
    virtual void OnLookUp(float inScale);

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

    virtual void PossessedByPlayerController(AEvePlayerController* playerController);

protected:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
};


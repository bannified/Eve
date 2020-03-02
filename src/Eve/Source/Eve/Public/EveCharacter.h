// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EveCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEveCharacterInputDelegate, AEveCharacter*, character);

class AEvePlayerController;

class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;
class AGrippableLedge;

UCLASS(Blueprintable)
class AEveCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEveCharacter();

    AEveCharacter(const class FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

    /* Climbing Settings */

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UBoxComponent* LedgeDetectionBox;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float LedgeDetectionBoxForwardOffset;

    /* Stand/Crouching Settings */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float StandingCapsuleHalfHeight;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float StandingMeshVerticalOffset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float CrouchingCapsuleHalfHeight;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float CrouchingMeshVerticalOffset;

public:
    /* Environment Contextual */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EveCharacter")
    float GroundDetectProjectionDistance;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "EveCharacter")
    bool bIsReachingGround;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EveCharacter")
    FName RightHandSocketName;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EveCharacter")
    FName LeftHandSocketName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Climbing")
    float HandDetectionSphereRadius;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Climbing")
    float LedgeDetectionRange;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Climbing")
    float LedgeDetectionHeightStart;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Climbing")
    float LedgeDetectionHeightEnd;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EveCharacter")
    TArray<TEnumAsByte<EObjectTypeQuery>> TraversalObjectTypes;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Climbing")
    float ClimbOffset;

    /* Character movement properties */
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Climbing")
    bool bIsCrouching;

public: 

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

    /* Crouch Input */
    virtual void OnCrouchStart();
    virtual void OnCrouchEnd();

    UPROPERTY(BlueprintAssignable, Category = "EveCharacter")
    FOnEveCharacterInputDelegate MoveRightEvent;
    UPROPERTY(BlueprintAssignable, Category = "EveCharacter")
    FOnEveCharacterInputDelegate MoveForwardEvent;

protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "EveCharacter")
    void BP_OnJumpStart();
    UFUNCTION(BlueprintImplementableEvent, Category = "EveCharacter")
    void BP_OnJumpEnd();

    UFUNCTION(BlueprintImplementableEvent, Category = "EveCharacter")
    void BP_OnCrouchStart();
    UFUNCTION(BlueprintImplementableEvent, Category = "EveCharacter")
    void BP_OnCrouchEnd();

    /* Custom movement modes */

    UFUNCTION()
    void HandleLedgeDetectionBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintCallable, Category = "EveCharacter")
    void StartGrippingLedge(AGrippableLedge* ledgeActor);

    UFUNCTION(BlueprintCallable, Category = "EveCharacter")
    void ReleaseGrip();

    UFUNCTION(BlueprintCallable, Category = "EveCharacter")
    void CheckForClimbTarget();
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EveCharacter")
    float JumpRange;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EveCharacter")
    bool bFoundClimbTarget;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EveCharacter")
    FVector ClimbTargetPoint;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EveCharacter")
    bool bCanGripEdge;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EveCharacter")
    bool bIsGrippingEdge;

    /* Stand/Crouch */
    UFUNCTION(BlueprintCallable, Category = "EveCharacter")
    void EnterCrouch();
    
    UFUNCTION(BlueprintCallable, Category = "EveCharacter")
    void ExitCrouch();

    /* End Movement */

    /* Environment Context */

    UFUNCTION(BlueprintCallable, Category = "EveCharacter")
    virtual bool IsReachingGround(float distance);

    UFUNCTION(BlueprintCallable, Category = "EveCharacter")
    virtual bool IsHandOnTraversal();

public: 
    /* Look */
    virtual void OnLookRight(float inScale);
    virtual void OnLookUp(float inScale);

    virtual void BeginPlay() override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

    virtual void PossessedByPlayerController(AEvePlayerController* playerController);
};


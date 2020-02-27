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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UBoxComponent* LedgeDetectionBox;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    float LedgeDetectionBoxForwardOffset;

public:
    /* Environment Contextual */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EveCharacter|Contextual")
    float GroundDetectProjectionDistance;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "EveCharacter|Contextual")
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

    UPROPERTY(BlueprintAssignable, Category = "EveCharacter")
    FOnEveCharacterInputDelegate MoveRightEvent;
    UPROPERTY(BlueprintAssignable, Category = "EveCharacter")
    FOnEveCharacterInputDelegate MoveForwardEvent;

protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "EveCharacter")
    void BP_OnJumpStart();
    UFUNCTION(BlueprintImplementableEvent, Category = "EveCharacter")
    void BP_OnJumpEnd();

    /* Custom movement modes */

    UFUNCTION()
    void HandleLedgeDetectionBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintCallable, Category = "EveCharacter")
    void StartGrippingLedge(AGrippableLedge* ledgeActor);

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


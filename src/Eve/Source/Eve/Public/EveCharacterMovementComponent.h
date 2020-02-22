// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EveCharacterMovementComponent.generated.h"

class AEveCharacter;

/**
 * 
 */
UCLASS()
class EVE_API UEveCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

    UEveCharacterMovementComponent(const class FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climbing")
    float EdgeShimmySpeed;

    virtual void SetUpdatedComponent(USceneComponent* NewUpdatedComponent) override;


    virtual void SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode = 0) override;

protected:
    virtual void PhysCustom(float deltaTime, int32 Iterations) override;

    virtual void PostLoad() override;

    AEveCharacter* OwnerEveCharacter;

private:
    void PhysCustomClimb(float deltaTime, int32 Iterations);
};

// Fill out your copyright notice in the Description page of Project Settings.
#include "EveCharacterMovementComponent.h"

#include "Eve/Eve.h"
#include "EveCharacter.h"

UEveCharacterMovementComponent::UEveCharacterMovementComponent(const class FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
    : Super(ObjectInitializer)
{
    EdgeShimmySpeed = 5.0f;
}

void UEveCharacterMovementComponent::SetUpdatedComponent(USceneComponent* NewUpdatedComponent)
{
    Super::SetUpdatedComponent(NewUpdatedComponent);
    if (OwnerEveCharacter == nullptr) {
        OwnerEveCharacter = Cast<AEveCharacter>(PawnOwner);
    }
}

void UEveCharacterMovementComponent::SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode /*= 0*/)
{
    Super::SetMovementMode(NewMovementMode, NewCustomMode);
    if (OwnerEveCharacter == nullptr) {
        OwnerEveCharacter = Cast<AEveCharacter>(PawnOwner);
    }

    if (NewMovementMode != EMovementMode::MOVE_Custom) {
        return;
    }

    switch (CustomMovementMode) {
    case CUSTOM_MOVEMENT_CLIMB:
        PRINT_ONSCREEN_INFO("%s is in Climb mode.", *(OwnerEveCharacter->GetName()));
        break;
    default:
        PRINT_ONSCREEN_INFO("Switching to an invalid custom movement mode for %s.", *(OwnerEveCharacter->GetName()));
        break;
    }
}

void UEveCharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
    Super::PhysCustom(deltaTime, Iterations);

    switch (CustomMovementMode) {
    case CUSTOM_MOVEMENT_CLIMB:
        PhysCustomClimb(deltaTime, Iterations);
        break;
    default:
        PRINT_WARN("Invalid Custom Movement mode being used.");
        break;
    }
}

void UEveCharacterMovementComponent::PostLoad()
{
    Super::PostLoad();

    OwnerEveCharacter = Cast<AEveCharacter>(PawnOwner);
}

void UEveCharacterMovementComponent::PhysCustomClimb(float deltaTime, int32 Iterations)
{
}

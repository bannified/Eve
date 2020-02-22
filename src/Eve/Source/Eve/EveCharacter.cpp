// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EveCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

AEveCharacter::AEveCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

	// Create a camera boom...
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bDoCollisionTest = true;

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void AEveCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}

void AEveCharacter::PossessedByPlayerController(AEvePlayerController* playerController)
{

}

void AEveCharacter::OnMoveRight(float inScale)
{
    FRotator rot = FRotator(0, 0, 0);

    UKismetMathLibrary::BreakRotator(GetControlRotation(), rot.Roll, rot.Pitch, rot.Yaw);
    rot.Roll = 0;
    rot.Pitch = 0;

    FVector resultVector = UKismetMathLibrary::GetRightVector(rot);

    AddMovementInput(resultVector, inScale);

    MoveRightEvent.Broadcast(this);
}

void AEveCharacter::OnMoveForward(float inScale)
{
    FRotator rot = FRotator(0, 0, 0);

    UKismetMathLibrary::BreakRotator(GetControlRotation(), rot.Roll, rot.Pitch, rot.Yaw);
    rot.Roll = 0;
    rot.Pitch = 0;

    FVector resultVector = UKismetMathLibrary::GetForwardVector(rot);

    AddMovementInput(resultVector, inScale);

    MoveRightEvent.Broadcast(this);
}

void AEveCharacter::OnLookUp(float inScale)
{
    Super::AddControllerPitchInput(inScale);
}

void AEveCharacter::OnLookRight(float inScale)
{
    Super::AddControllerYawInput(inScale);
}

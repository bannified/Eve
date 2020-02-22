// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EvePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "EveCharacter.h"
#include "Engine/World.h"

AEvePlayerController::AEvePlayerController()
{
}

void AEvePlayerController::OnMoveRightInput(float inScale)
{
	if (m_CharacterBase != nullptr) 
	{
		m_CharacterBase->OnMoveRight(inScale);
	}

    ReceiveMoveRightInput.Broadcast(this);
}

void AEvePlayerController::OnMoveForwardInput(float inScale)
{
	if (m_CharacterBase != nullptr)
	{
		m_CharacterBase->OnMoveForward(inScale);
	}

	ReceiveMoveForwardInput.Broadcast(this);
}

void AEvePlayerController::OnJumpStart()
{
    if (m_CharacterBase != nullptr) {
        m_CharacterBase->OnJumpStart();
    }
}

void AEvePlayerController::OnJumpEnd()
{
    if (m_CharacterBase != nullptr) {
        m_CharacterBase->OnJumpEnd();
    }
}

void AEvePlayerController::OnLookRightInput(float inScale)
{
    if (m_CharacterBase != nullptr) {
        m_CharacterBase->OnLookRight(inScale);
    }
}

void AEvePlayerController::OnLookUpInput(float inScale)
{
    if (m_CharacterBase != nullptr) {
        m_CharacterBase->OnLookUp(inScale);
    }
}

void AEvePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void AEvePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

    InputComponent->BindAxis("MoveForward", this, &AEvePlayerController::OnMoveForwardInput);
    InputComponent->BindAxis("MoveRight", this, &AEvePlayerController::OnMoveRightInput);

    InputComponent->BindAxis("LookUp", this, &AEvePlayerController::OnLookUpInput);
    InputComponent->BindAxis("LookRight", this, &AEvePlayerController::OnLookRightInput);

    InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AEvePlayerController::OnJumpStart);
    InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AEvePlayerController::OnJumpEnd);
}

void AEvePlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);

    AEveCharacter* character = Cast<AEveCharacter>(GetPawn());
    if (character != nullptr)
    {
        m_CharacterBase = character;
        m_CharacterBase->PossessedByPlayerController(this);
    }
}

void AEvePlayerController::OnUnPossess()
{
    Super::OnUnPossess();
}

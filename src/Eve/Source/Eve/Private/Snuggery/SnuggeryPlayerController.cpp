// Fill out your copyright notice in the Description page of Project Settings.

#include "Snuggery/SnuggeryPlayerController.h"
#include "Eve/Eve.h"
#include "Snuggery/SnuggeryCharacter.h"

void ASnuggeryPlayerController::OnMoveRightInput(float inScale)
{
    if (SnuggeryCharacter != nullptr) {
        SnuggeryCharacter->OnMoveRight(inScale);
    }
}

void ASnuggeryPlayerController::OnMoveForwardInput(float inScale)
{
    if (SnuggeryCharacter != nullptr) {
        SnuggeryCharacter->OnMoveForward(inScale);
    }
}

void ASnuggeryPlayerController::OnJumpStart()
{
    if (SnuggeryCharacter != nullptr) {
        SnuggeryCharacter->OnJumpStart();
    }
}

void ASnuggeryPlayerController::OnJumpEnd()
{
    if (SnuggeryCharacter != nullptr) {
        SnuggeryCharacter->OnJumpEnd();
    }
}

void ASnuggeryPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis("MoveForward", this, &ASnuggeryPlayerController::OnMoveForwardInput);
    InputComponent->BindAxis("MoveRight", this, &ASnuggeryPlayerController::OnMoveRightInput);

    InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASnuggeryPlayerController::OnJumpStart);
    InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ASnuggeryPlayerController::OnJumpEnd);

}

void ASnuggeryPlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);

    SnuggeryCharacter = Cast<ASnuggeryCharacter>(aPawn);

    if (SnuggeryCharacter == nullptr) {
        PRINT_ONSCREEN_WARN("SnuggeryPlayerController %s does not have a valid pawn %s.", *(this->GetName()), *(aPawn->GetName()));
        return;
    }

    SnuggeryCharacter->OnPossessedByPlayerController(this);
}

void ASnuggeryPlayerController::OnUnPossess()
{
    Super::OnUnPossess();

    SnuggeryCharacter = nullptr;
}

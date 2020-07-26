// Fill out your copyright notice in the Description page of Project Settings.

#include "Snuggery/SnuggeryPlayerController.h"
#include "Eve/Eve.h"
#include "Snuggery/SnuggeryCharacterBase.h"
#include "Net/UnrealNetwork.h"
#include "EveCore/EveGameStateBase.h"
#include "Kismet/GameplayStatics.h"

void ASnuggeryPlayerController::OnTurn(float inScale)
{
    if (SnuggeryCharacter != nullptr)
    {
        //SnuggeryCharacter->
    }
}

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

void ASnuggeryPlayerController::OnLookRightInput(float inScale)
{
    if (SnuggeryCharacter != nullptr)
    {
        SnuggeryCharacter->OnLookRight(inScale);
    }
}

void ASnuggeryPlayerController::OnLookUpInput(float inScale)
{
    if (SnuggeryCharacter != nullptr)
    {
        SnuggeryCharacter->OnLookUp(inScale);
    }
}

void ASnuggeryPlayerController::OnCameraPanStart()
{
    if (SnuggeryCharacter != nullptr)
    {
        SnuggeryCharacter->OnCameraPanStart();
    }
}

void ASnuggeryPlayerController::OnCameraPanEnd()
{
    if (SnuggeryCharacter != nullptr)
    {
        SnuggeryCharacter->OnCameraPanEnd();
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

    InputComponent->BindAxis("LookUp", this, &ASnuggeryPlayerController::OnLookUpInput);
    InputComponent->BindAxis("LookRight", this, &ASnuggeryPlayerController::OnLookRightInput);

    InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASnuggeryPlayerController::OnJumpStart);
    InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ASnuggeryPlayerController::OnJumpEnd);

    InputComponent->BindAction("CameraPan", EInputEvent::IE_Pressed, this, &ASnuggeryPlayerController::OnCameraPanStart);
    InputComponent->BindAction("CameraPan", EInputEvent::IE_Released, this, &ASnuggeryPlayerController::OnCameraPanEnd);

}

void ASnuggeryPlayerController::OnPossess(APawn* aPawn)
{
    SnuggeryCharacter = Cast<ASnuggeryCharacterBase>(GetPawn());

    Super::OnPossess(aPawn);

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

void ASnuggeryPlayerController::BeginPlay()
{
    bShowMouseCursor = true;
}

void ASnuggeryPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ASnuggeryPlayerController, SnuggeryCharacter);
}

void ASnuggeryPlayerController::RegisterPlayerState_Server_Implementation()
{
    UWorld* world = GetWorld();
    AEveGameStateBase* gameState = Cast<AEveGameStateBase>(UGameplayStatics::GetGameState(world));

    gameState->RegisterPlayerState_Server(GetPlayerState<APlayerState>());
}

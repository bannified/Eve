// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/SnuggeryCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Snuggery/SnuggeryGameMode.h"
#include "Snuggery/SnuggeryPlayerState.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"
#include "Snuggery/SnuggeryPetCharacter.h"
#include "Eve/Eve.h"
#include "UI/Widgets/PlayerLabelWidget.h"
#include "Snuggery/SnuggeryHUD.h"
#include "UI/Widgets/ChatBubbleWidget.h"

// Sets default values
ASnuggeryCharacter::ASnuggeryCharacter() : ASnuggeryCharacterBase()
{
    bCameraPanEnabled = false;

    CameraHorizontalPanSpeed = 1.0f;
    CameraVerticalPanSpeed = 1.0f;

    CameraMode = ESnuggeryCharacterCameraMode::PlayerPivot;
    SetupCameraMode(CameraMode);

    ChatMessageRevealDuration = 5.0f;
}

void ASnuggeryCharacter::OnMoveRight(float inScale)
{
    FRotator rot = FRotator(0, 0, 0);
    UKismetMathLibrary::BreakRotator(GetControlRotation(), rot.Roll, rot.Pitch, rot.Yaw);
    rot.Roll = 0;
    rot.Pitch = 0;

    AddMovementInput(UKismetMathLibrary::GetRightVector(rot), inScale);
}

void ASnuggeryCharacter::OnMoveForward(float inScale)
{
    FRotator rot = FRotator(0, 0, 0);
    UKismetMathLibrary::BreakRotator(GetControlRotation(), rot.Roll, rot.Pitch, rot.Yaw);
    rot.Roll = 0;
    rot.Pitch = 0;

    AddMovementInput(UKismetMathLibrary::GetForwardVector(rot), inScale);
}

void ASnuggeryCharacter::OnJumpStart()
{
    Jump();
}

void ASnuggeryCharacter::OnJumpEnd()
{

}

void ASnuggeryCharacter::OnLookRight(float inScale)
{
    // Todo: Refactor into CameraController
    switch (CameraMode)
    {
        case ESnuggeryCharacterCameraMode::PlayerPivot:
            if (bIsPlayerPanning)
            {
                Super::AddControllerYawInput(inScale);
            }
            break;
        case ESnuggeryCharacterCameraMode::Platformer:
            break;
        case ESnuggeryCharacterCameraMode::ThirdPerson:
            Super::AddControllerYawInput(inScale);
            break;
    }
}

void ASnuggeryCharacter::OnLookUp(float inScale)
{
    // Todo: Refactor into CameraController
    switch (CameraMode)
    {
    case ESnuggeryCharacterCameraMode::PlayerPivot:
        if (bIsPlayerPanning)
        {
            Super::AddControllerPitchInput(inScale);
        }
        break;
    case ESnuggeryCharacterCameraMode::Platformer:
        break;
    case ESnuggeryCharacterCameraMode::ThirdPerson:
        Super::AddControllerPitchInput(inScale);
        break;
    }
    Super::AddControllerPitchInput(inScale);
}

void ASnuggeryCharacter::OnCameraPanStart()
{
    bIsPlayerPanning = true;
}

void ASnuggeryCharacter::OnCameraPanEnd()
{
    bIsPlayerPanning = false;
}

void ASnuggeryCharacter::SetupCameraMode(TEnumAsByte<ESnuggeryCharacterCameraMode> mode)
{
    switch (mode)
    {
    case ESnuggeryCharacterCameraMode::PlayerPivot:
        bUseControllerRotationPitch = false;
        bUseControllerRotationYaw = false;
        bUseControllerRotationRoll = false;

        SpringArmComponent->bUsePawnControlRotation = true;
        SpringArmComponent->bInheritPitch = true;
        SpringArmComponent->bInheritYaw = true;
        SpringArmComponent->bInheritRoll = true;
        SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
        SpringArmComponent->SetRelativeRotation(FRotator(-25.0f, -0.0f, 0.0f));

        CameraComponent->bUsePawnControlRotation = false;
        CameraComponent->SetRelativeRotation(FRotator::ZeroRotator);

        bCameraPanEnabled = true;
        break;
    case ESnuggeryCharacterCameraMode::Platformer:
        bUseControllerRotationPitch = false;
        bUseControllerRotationYaw = false;
        bUseControllerRotationRoll = false;

        SpringArmComponent->bUsePawnControlRotation = true;
        SpringArmComponent->bInheritPitch = false;
        SpringArmComponent->bInheritYaw = false;
        SpringArmComponent->bInheritRoll = false;
        SpringArmComponent->SetRelativeLocation(FVector(0.0f, -0.0f, 50.0f));
        SpringArmComponent->SetRelativeRotation(FRotator(-25.0f, 180.0f, 0.0f));

        CameraComponent->bUsePawnControlRotation = false;
        CameraComponent->SetRelativeRotation(FRotator::ZeroRotator);

        bCameraPanEnabled = false;
        break;
    case ESnuggeryCharacterCameraMode::ThirdPerson:
        bUseControllerRotationPitch = false;
        bUseControllerRotationYaw = false;
        bUseControllerRotationRoll = false;

        SpringArmComponent->bUsePawnControlRotation = true;
        SpringArmComponent->bInheritPitch = true;
        SpringArmComponent->bInheritYaw = true;
        SpringArmComponent->bInheritRoll = true;
        SpringArmComponent->SetRelativeLocation(FVector(0.0f, 60.0f, 70.0f));
        SpringArmComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 00.0f));

        CameraComponent->bUsePawnControlRotation = false;
        CameraComponent->SetRelativeRotation(FRotator::ZeroRotator);

        bCameraPanEnabled = false;
        break;
    default:
        break;
    }
}

void ASnuggeryCharacter::PlaySpawnEffect()
{
    if (SpawnParticleSystem == nullptr) 
    {
        return;
    }
    FVector location = GetActorLocation();
    float heightOffset = GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2.0f;
    location.Z -= heightOffset;
    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnParticleSystem, location, FRotator::ZeroRotator, SpawnParticleScale);
}

void ASnuggeryCharacter::SetupPlayerNameLabel()
{
    if (NameLabelWidgetComponent->GetUserWidgetObject() == nullptr)
    {
        NameLabelWidgetComponent->InitWidget();
    }

    UPlayerLabelWidget* labelWidget = Cast<UPlayerLabelWidget>(NameLabelWidgetComponent->GetUserWidgetObject());

    labelWidget->SetupWithPlayer(this);
}

void ASnuggeryCharacter::ChangeName_Server_Implementation(const FString& newName)
{
    UGameplayStatics::GetGameMode(GetWorld())->ChangeName(GetController(), newName, false);
}

void ASnuggeryCharacter::SwitchCharacter_Server(USnuggeryCharacterDataAsset* characterData)
{
    Super::SwitchCharacter_Server(characterData);
}

void ASnuggeryCharacter::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    static FName Name_CameraMode = GET_MEMBER_NAME_CHECKED(ASnuggeryCharacter, CameraMode);

    UProperty* PropertyThatChanged = PropertyChangedEvent.Property;
    const FName PropertyName = PropertyThatChanged != nullptr ? PropertyThatChanged->GetFName() : NAME_None;

    if (PropertyName == Name_CameraMode)
    {
        SetupCameraMode(CameraMode);
    }
}

void ASnuggeryCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    
    // For Server/ListenServer
    SetupPlayerNameLabel();
}

void ASnuggeryCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    // For Clients
    SetupPlayerNameLabel();
}

void ASnuggeryCharacter::SendMessage_Implementation(const FString& message)
{
    AGameModeBase* gameMode = UGameplayStatics::GetGameMode(GetWorld());
    ASnuggeryGameMode* casted = Cast<ASnuggeryGameMode>(gameMode);

    APlayerState* playerState = GetPlayerState();
    ASnuggeryPlayerState* castedState = Cast<ASnuggeryPlayerState>(playerState);
    casted->ProcessPlayerMessage(castedState, message);
}

void ASnuggeryCharacter::ReceiveMessage_Implementation(ASnuggeryPlayerState* sender, const FString& message)
{
    AHUD* hud = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD();
    ASnuggeryHUD* snuggeryHud = Cast<ASnuggeryHUD>(hud);

    if (snuggeryHud != nullptr)
    {
        snuggeryHud->GetChatboxWidget()->AddMessageToChatHistoryBox(sender->GetPlayerName(), message);
    }

    FString formatted = FString::Printf(TEXT("%s: %s"), *sender->GetPlayerName(), *message);

    ASnuggeryCharacter* senderCharacter = sender->GetPawn<ASnuggeryCharacter>();

    UChatBubbleWidget* chatBubble = Cast<UChatBubbleWidget>(senderCharacter->ChatBubbleWidgetComponent->GetUserWidgetObject());
    chatBubble->ShowWithMessage(formatted, ChatMessageRevealDuration);

    OnMessageReceived(sender, message);
}

void ASnuggeryCharacter::SwitchCharacter_Multicast(USnuggeryCharacterDataAsset* characterData)
{
    Super::SwitchCharacter_Multicast(characterData);
}

// Called when the game starts or when spawned
void ASnuggeryCharacter::BeginPlay()
{
	Super::BeginPlay();
    PlaySpawnEffect();

    if (Role == ENetRole::ROLE_Authority)
    {
        if (StarterPetClass != nullptr)
        {
            FActorSpawnParameters parameters;
            parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            ASnuggeryPetCharacter* pet = GetWorld()->SpawnActor<ASnuggeryPetCharacter>(StarterPetClass, GetActorLocation(), FRotator::ZeroRotator, parameters);
            CurrentPet = pet;
            CurrentPet->SetPetOwner_Server(this);
        }
    }
}

// Called every frame
void ASnuggeryCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


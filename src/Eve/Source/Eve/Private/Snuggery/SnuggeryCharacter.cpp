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
#include "Snuggery/DataAssets/SnuggeryCharacterDataAsset.h"
#include "Eve/Eve.h"

// Sets default values
ASnuggeryCharacter::ASnuggeryCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SetReplicates(true);
    SetReplicateMovement(true);

    bUseControllerRotationYaw = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
    GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

    // Create a camera boom...
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->TargetArmLength = 500.0f;

    SpringArmComponent->ProbeChannel = ECC_Visibility;
    SpringArmComponent->bDoCollisionTest = true;

    SpringArmComponent->bInheritPitch = false;
    SpringArmComponent->bInheritYaw = false;
    SpringArmComponent->bInheritRoll = false;

    // Create a camera...
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
    CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

    // Name Label Widget Component
    NameLabelWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameLabelWidgetComponent"));
    NameLabelWidgetComponent->SetupAttachment(RootComponent);
    NameLabelWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    NameLabelWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -120.0f));

    // Chat Bubble Widget Component
    ChatBubbleWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ChatBubbleWidgetComponent"));
    ChatBubbleWidgetComponent->SetupAttachment(RootComponent);
    ChatBubbleWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    ChatBubbleWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));

    bCameraPanEnabled = false;

    CameraHorizontalPanSpeed = 1.0f;
    CameraVerticalPanSpeed = 1.0f;

    CameraMode = ESnuggeryCharacterCameraMode::PlayerPivot;
    SetupCameraMode(CameraMode);
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

void ASnuggeryCharacter::SwitchCharacter_Multicast_Implementation(USnuggeryCharacterDataAsset* characterData)
{
    characterData->InitializeCharacter(this);
    PlaySpawnEffect();
    BP_OnSwitchCharacter(characterData);
}

void ASnuggeryCharacter::SwitchCharacter_Server_Implementation(USnuggeryCharacterDataAsset* characterData)
{
    SwitchCharacter_Multicast(characterData);
}

void ASnuggeryCharacter::OnPossessedByPlayerController(ASnuggeryPlayerController* playerController)
{

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
    OnMessageReceived(sender, message);
}

// Called when the game starts or when spawned
void ASnuggeryCharacter::BeginPlay()
{
	Super::BeginPlay();
    PlaySpawnEffect();
}

// Called every frame
void ASnuggeryCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


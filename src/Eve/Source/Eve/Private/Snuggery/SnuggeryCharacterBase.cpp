// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/SnuggeryCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Snuggery/DataAssets/SnuggeryCharacterDataAsset.h"

// Sets default values
ASnuggeryCharacterBase::ASnuggeryCharacterBase()
{
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
}

void ASnuggeryCharacterBase::OnPossessedByPlayerController(ASnuggeryPlayerController* playerController)
{

}

// Called when the game starts or when spawned
void ASnuggeryCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASnuggeryCharacterBase::OnMoveRight(float inScale)
{
    BP_OnMoveRight(inScale);
}

void ASnuggeryCharacterBase::OnMoveForward(float inScale)
{
    BP_OnMoveForward(inScale);
}

void ASnuggeryCharacterBase::OnJumpStart()
{
    BP_OnJumpStart();
}

void ASnuggeryCharacterBase::OnJumpEnd()
{
    BP_OnJumpEnd();
}

void ASnuggeryCharacterBase::OnLookRight(float inScale)
{
    BP_OnLookRight(inScale);
}

void ASnuggeryCharacterBase::OnLookUp(float inScale)
{
    BP_OnLookUp(inScale);
}

void ASnuggeryCharacterBase::OnCameraPanStart()
{
    BP_OnCameraPanStart();
}

void ASnuggeryCharacterBase::OnCameraPanEnd()
{
    BP_OnCameraPanEnd();
}

void ASnuggeryCharacterBase::PlaySpawnEffect()
{

}

void ASnuggeryCharacterBase::SwitchCharacter_Multicast_Implementation(USnuggeryCharacterDataAsset* characterData)
{
    characterData->InitializeCharacter(this);
    PlaySpawnEffect();
    BP_OnSwitchCharacter(characterData);
}

void ASnuggeryCharacterBase::SwitchCharacter_Server_Implementation(USnuggeryCharacterDataAsset* characterData)
{
    SwitchCharacter_Multicast(characterData);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/SnuggeryCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

void ASnuggeryCharacter::OnPossessedByPlayerController(ASnuggeryPlayerController* playerController)
{

}

// Called when the game starts or when spawned
void ASnuggeryCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnuggeryCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


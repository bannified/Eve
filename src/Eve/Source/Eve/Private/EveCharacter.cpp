// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EveCharacter.h"
#include "Eve/Eve.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EveCharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GrippableLedge.h"

AEveCharacter::AEveCharacter(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer.SetDefaultSubobjectClass<UEveCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
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

    // Creating ledge detection
    LedgeDetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LedgeDetectionBox"));
    LedgeDetectionBox->SetBoxExtent(FVector(5.0f, 45.0f, 10.0f));
    LedgeDetectionBox->SetRelativeLocation(FVector(60.0f, 0.0f, 110.0f));
    LedgeDetectionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    LedgeDetectionBox->SetCollisionResponseToChannel(OBJECT_TYPE_TRAVERSAL, ECR_Overlap);
    LedgeDetectionBox->SetCollisionObjectType(OBJECT_TYPE_CHARACTER_TRAVERSAL);
    LedgeDetectionBox->SetupAttachment(RootComponent);

    GroundDetectProjectionDistance = 10.0f;

    TraversalObjectTypes = TArray<TEnumAsByte<EObjectTypeQuery>>();
    TraversalObjectTypes.Add(TEnumAsByte<EObjectTypeQuery>(OBJECT_TYPE_TRAVERSAL));

    RightHandSocketName = FName("handgrip_r");
    LeftHandSocketName = FName("handgrip_l");

    HandDetectionSphereRadius = 5.0f;
    LedgeDetectionRange = 5.0f;
    LedgeDetectionHeightStart = 30.0f;
    LedgeDetectionHeightEnd = 35.0f;

    StandingCapsuleHalfHeight = 96.0f;
    StandingMeshVerticalOffset = -88.0f;

    CrouchingCapsuleHalfHeight = 48.0f;
    CrouchingMeshVerticalOffset = -44.0f;

    JumpRange = 200.0f;
}

void AEveCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    bIsReachingGround = (GetMovementComponent()->Velocity.Z < 0) && IsReachingGround(GroundDetectProjectionDistance);

    CheckForClimbTarget();
}

void AEveCharacter::PossessedByPlayerController(AEvePlayerController* playerController)
{

}

void AEveCharacter::OnMoveRight(float inScale)
{
    if (GetCharacterMovement()->CustomMovementMode == CUSTOM_MOVEMENT_CLIMB) {

    }
    else {
        FRotator rot = FRotator(0, 0, 0);

        UKismetMathLibrary::BreakRotator(GetControlRotation(), rot.Roll, rot.Pitch, rot.Yaw);
        rot.Roll = 0;
        rot.Pitch = 0;

        FVector resultVector = UKismetMathLibrary::GetRightVector(rot);

        AddMovementInput(resultVector, inScale);

        MoveRightEvent.Broadcast(this);
    }
}

void AEveCharacter::OnMoveForward(float inScale)
{
    if (GetCharacterMovement()->CustomMovementMode == CUSTOM_MOVEMENT_CLIMB) {

    }
    else {
        FRotator rot = FRotator(0, 0, 0);

        UKismetMathLibrary::BreakRotator(GetControlRotation(), rot.Roll, rot.Pitch, rot.Yaw);
        rot.Roll = 0;
        rot.Pitch = 0;

        FVector resultVector = UKismetMathLibrary::GetForwardVector(rot);

        AddMovementInput(resultVector, inScale);

        MoveForwardEvent.Broadcast(this);
    }
}

void AEveCharacter::OnJumpStart()
{
    BP_OnJumpStart();

    if (GetCharacterMovement()->CustomMovementMode == CUSTOM_MOVEMENT_CLIMB) {
        
    }
    else {
        Jump();

        if (JumpCurrentCount < JumpMaxCount && bFoundClimbTarget && !bIsGrippingEdge) {
            FRotator lookAtTargetDir = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ClimbTargetPoint);
            FRotator resultRot = GetActorRotation();
            resultRot.Yaw = lookAtTargetDir.Yaw;
            SetActorRotation(resultRot, ETeleportType::TeleportPhysics);
        }
    }

}

void AEveCharacter::OnJumpEnd()
{
    BP_OnJumpEnd();
    if (GetCharacterMovement()->CustomMovementMode == CUSTOM_MOVEMENT_CLIMB) {

    }
    else {

    }
}

void AEveCharacter::OnCrouchStart()
{
    BP_OnCrouchStart();
    if (GetCharacterMovement()->CustomMovementMode == CUSTOM_MOVEMENT_CLIMB) {
        ReleaseGrip();
    }
    else {
        bIsCrouching = !bIsCrouching;
        if (bIsCrouching) {
            EnterCrouch();
        }
        else {
            ExitCrouch();
        }
    }
}

void AEveCharacter::OnCrouchEnd()
{
    BP_OnCrouchEnd();
    if (GetCharacterMovement()->CustomMovementMode == CUSTOM_MOVEMENT_CLIMB) {
    }
    else {

    }
}

void AEveCharacter::HandleLedgeDetectionBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherComp->GetCollisionObjectType() == OBJECT_TYPE_TRAVERSAL) {
        bCanGripEdge = true;
    }

    if (bCanGripEdge && !bIsGrippingEdge) {
        AGrippableLedge* ledge = Cast<AGrippableLedge>(OtherActor);
        if (ledge != nullptr) {
            StartGrippingLedge(ledge);
        }
    }
}

void AEveCharacter::StartGrippingLedge(AGrippableLedge* ledgeActor)
{
    bIsGrippingEdge = true;
    GetCharacterMovement()->SetMovementMode(MOVE_Custom, CUSTOM_MOVEMENT_CLIMB);

    FVector2D ledgePos2D(ledgeActor->GetActorLocation());
    FVector dir = ledgeActor->GetUnitDirectionVectorToPosition(GetActorLocation());
    FVector perp = dir.RotateAngleAxis(90.0f, { 0.0f, 0.0f, 1.0f });
    FVector2D perp2D(perp);
    FRotator lookAt = dir.ToOrientationRotator();
    FVector actorLocation = GetActorLocation();
    FVector locationDiff = actorLocation - ledgeActor->GetActorLocation();
    FVector2D diff2D(locationDiff);
    float dot = FVector2D::DotProduct(perp2D, diff2D);

    FVector2D targetLedgePosition = ledgePos2D + dot * perp2D;

    SetActorRotation(lookAt);
    float x = targetLedgePosition.X - dir.X * LedgeDetectionBoxForwardOffset;
    float y = targetLedgePosition.Y - dir.Y * LedgeDetectionBoxForwardOffset;
    float z = actorLocation.Z + ledgeActor->GetActorLocation().Z - LedgeDetectionBox->GetComponentLocation().Z;

    SetActorLocation(FVector(x, y, z));
}

void AEveCharacter::ReleaseGrip()
{
    GetCharacterMovement()->SetMovementMode(MOVE_Falling, 0);
    GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);
    bIsGrippingEdge = false;
}

void AEveCharacter::CheckForClimbTarget()
{
    FVector start = GetActorLocation();
    FVector end = start + GetActorRotation().Vector() * JumpRange;
    float capsuleHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
    FVector boxScale(capsuleHalfHeight, capsuleHalfHeight, capsuleHalfHeight * 2);

    FHitResult hit;
    bFoundClimbTarget = UKismetSystemLibrary::BoxTraceSingleForObjects(GetWorld(), GetActorLocation(), end, boxScale, GetActorRotation(),
        TraversalObjectTypes, false, {}, EDrawDebugTrace::ForOneFrame, hit, true);

    if (bFoundClimbTarget) {
        ClimbTargetPoint = hit.ImpactPoint;
    }
}

void AEveCharacter::EnterCrouch() 
{
    GetCharacterMovement()->Crouch();
    GetCapsuleComponent()->SetCapsuleHalfHeight(CrouchingCapsuleHalfHeight);
    GetCapsuleComponent()->AddLocalOffset(FVector(0.0f, 0.0f, -CrouchingCapsuleHalfHeight / 2.0f));
    GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, CrouchingMeshVerticalOffset));
}

void AEveCharacter::ExitCrouch()
{
    GetCharacterMovement()->UnCrouch();
    GetCapsuleComponent()->SetCapsuleHalfHeight(StandingCapsuleHalfHeight);
    GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, StandingMeshVerticalOffset));
}

bool AEveCharacter::IsReachingGround(float distance)
{
    UCapsuleComponent* body = GetCapsuleComponent();
    float offsetToBottom = body->GetScaledCapsuleHalfHeight();

    FVector traceStartLocation = GetActorLocation() - FVector(0.0f, 0.0f, offsetToBottom);
    FVector traceEndLocation = traceStartLocation - FVector(0.0f, 0.0f, distance);
    
    FCollisionObjectQueryParams objectQueryParams(ECC_WorldStatic);

    FHitResult hit;
    bool hitSuccess = GetWorld()->LineTraceSingleByObjectType(hit, traceStartLocation, traceEndLocation, objectQueryParams);

    return hitSuccess;
}

bool AEveCharacter::IsHandOnTraversal()
{
    FCollisionObjectQueryParams objectQueryParams(ECC_WorldStatic);

    FVector forward = UKismetMathLibrary::GetForwardVector(GetActorRotation());

    FVector start = GetActorLocation() + forward * LedgeDetectionRange + FVector(0.0f, 0.0f, LedgeDetectionHeightStart);
    FVector end = start + FVector(0.0f, 0.0f, LedgeDetectionHeightEnd);

    FHitResult hit;

    bool hitResult = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), start, end,
        HandDetectionSphereRadius, TraversalObjectTypes, false, {}, EDrawDebugTrace::ForOneFrame, hit, true);

    if (hitResult) {
        //ClimbOffset = hit.Actor->GetActorLocation().Z;
    }

    return hitResult;
}

void AEveCharacter::OnLookUp(float inScale)
{
    Super::AddControllerPitchInput(inScale);
}

void AEveCharacter::BeginPlay()
{
    Super::BeginPlay();
    LedgeDetectionBox->OnComponentBeginOverlap.AddDynamic(this, &AEveCharacter::HandleLedgeDetectionBoxOverlap);
    LedgeDetectionBoxForwardOffset = LedgeDetectionBox->GetRelativeLocation().X;

}

void AEveCharacter::OnLookRight(float inScale)
{
    Super::AddControllerYawInput(inScale);
}

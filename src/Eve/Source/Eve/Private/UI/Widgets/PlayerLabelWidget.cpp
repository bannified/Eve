// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PlayerLabelWidget.h"
#include "Snuggery/SnuggeryCharacter.h"
#include "Snuggery/SnuggeryPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Snuggery/SnuggeryCharacterBase.h"

UPlayerLabelWidget::UPlayerLabelWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    MaxScale = 1.0f;
    MinScale = 0.0f;

    LabelScaleNearPlaneDistanceSq = 0.0f;
    LabelScaleFarPlaneDistanceSq = 5000000.0f;
}

void UPlayerLabelWidget::SetupWithPlayer(ASnuggeryCharacterBase* snuggeryCharacter)
{
    OwnerCharacter = snuggeryCharacter;

    ASnuggeryPlayerState* playerState = Cast<ASnuggeryPlayerState>(OwnerCharacter->GetPlayerState());
    playerState->OnNameChange.AddDynamic(this, &UPlayerLabelWidget::UpdateName);

    UpdateName(playerState->GetPlayerName());
}

void UPlayerLabelWidget::UpdateName(const FString& newName)
{
    PlayerName = newName;

    BP_OnPlayerNameUpdate();
}

void UPlayerLabelWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    const UWorld* world = GetWorld();

    APlayerController* playerController = UGameplayStatics::GetPlayerController(world, 0);
    ASnuggeryCharacter* snuggeryCharacter = playerController->GetPawn<ASnuggeryCharacter>();

    LocalPlayerCamera = snuggeryCharacter->GetCameraComponent();
}

void UPlayerLabelWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (OwnerCharacter == nullptr || LocalPlayerCamera == nullptr)
    {
        return;
    }

    const FVector ownerLocation = OwnerCharacter->GetActorLocation();
    const FVector cameraLocation = LocalPlayerCamera->GetComponentLocation();

    float distance2D = UKismetMathLibrary::Vector_Distance2DSquared(ownerLocation, cameraLocation);
    distance2D = UKismetMathLibrary::NormalizeToRange(distance2D, LabelScaleNearPlaneDistanceSq, LabelScaleFarPlaneDistanceSq);

    float scaleAlpha = ScaleCurve->GetFloatValue(distance2D);
    float scale1D = FMath::Lerp(MinScale, MaxScale, scaleAlpha);

    SetRenderScale(FVector2D(scale1D, scale1D));
}

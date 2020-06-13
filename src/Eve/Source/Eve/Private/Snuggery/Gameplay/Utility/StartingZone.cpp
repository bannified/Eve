// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/Gameplay/Utility/StartingZone.h"
#include "Components/SceneComponent.h"
#include "Components/DecalComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AStartingZone::AStartingZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    StartingZoneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    SetRootComponent(StartingZoneRootComponent);

    VisualComponent = CreateDefaultSubobject<USceneComponent>(TEXT("VisualComponent"));
    VisualComponent->SetupAttachment(RootComponent);

    DecalGroup = CreateDefaultSubobject<USceneComponent>(TEXT("DecalGroup"));
    DecalGroup->SetupAttachment(RootComponent);
    FloorDecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("FloorDecal"));
    FloorDecalComponent->SetupAttachment(DecalGroup);
    DecalPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DecalPlane"));
    DecalPlane->SetupAttachment(DecalGroup);

    ZoneCollider = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ZoneCollider"));
    ZoneCollider->SetupAttachment(RootComponent);
    ZoneCollider->SetVisibility(false);
    ZoneCollider->SetHiddenInGame(true);
    ZoneCollider->CastShadow = false;

    ZoneCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ZoneCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    ZoneCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    ZoneCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
    ZoneCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    ZoneCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);

    DebugTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DebugTextRender"));
    DebugTextRenderComponent->bIsEditorOnly = true;
    DebugTextRenderComponent->SetupAttachment(RootComponent);
    DebugTextRenderComponent->SetText(TEXT("StartingZone"));
    DebugTextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
    DebugTextRenderComponent->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    DebugTextRenderComponent->SetWorldSize(100.0f);
    DebugTextRenderComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    DebugTextRenderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);

    UpdateZoneColliderBox();
}

void AStartingZone::ActivateZoneBoundary()
{
    ZoneCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AStartingZone::DeactivateZoneBoundary()
{
    ZoneCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AStartingZone::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    // Todo: Update Zone Collider Box if property changes.
}

void AStartingZone::UpdateZoneColliderBox()
{
    // Todo: Auto-resizing of ZoneColliderBox and line.
}

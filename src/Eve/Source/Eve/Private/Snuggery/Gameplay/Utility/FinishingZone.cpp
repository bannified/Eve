// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/Gameplay/Utility/FinishingZone.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Snuggery/SnuggeryCharacter.h"

// Sets default values
AFinishingZone::AFinishingZone()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));

    VisualComponent = CreateDefaultSubobject<USceneComponent>(TEXT("VisualComponent"));
    VisualComponent->SetupAttachment(RootComponent);

    BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
    BoxTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
    BoxTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AFinishingZone::BeginPlay()
{
	Super::BeginPlay();
	
    BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFinishingZone::OnComponentBeginOverlap);
}

void AFinishingZone::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    ASnuggeryCharacter* snuggeryCharacter = Cast<ASnuggeryCharacter>(OtherActor);
    if (snuggeryCharacter != nullptr)
    {
        OnPlayerEnterZone.Broadcast(snuggeryCharacter);
    }

    BP_OnComponentBeginOverlapZone(OverlappedComponent, OtherActor, OtherComp);

    OnBeginOverlapZone.Broadcast(OverlappedComponent, OtherActor, OtherComp);
}

void AFinishingZone::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    BoxTrigger->OnComponentBeginOverlap.RemoveAll(this);

    Super::EndPlay(EndPlayReason);
}

// Called every frame
void AFinishingZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


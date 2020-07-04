// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/Gameplay/GameModes/Run/RunLevelInfoObject.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Snuggery/Gameplay/Utility/StartingZone.h"
#include "Eve/Eve.h"
#include "Snuggery/Gameplay/Utility/FinishingZone.h"

void ARunLevelInfoObject::ScanLevelForData()
{
    const UWorld* world = GetWorld();

    AActor* startingZoneActor = UGameplayStatics::GetActorOfClass(world, AStartingZone::StaticClass());

    StartingZone = Cast<AStartingZone>(startingZoneActor);

    if (StartingZone == nullptr)
    {
        PRINT_ONSCREEN_WARN("No StartingZone can be found. Please add one to the level!");
    }

    AActor* finishingZoneActor = UGameplayStatics::GetActorOfClass(world, AFinishingZone::StaticClass());
    FinishingZone = Cast<AFinishingZone>(finishingZoneActor);

    if (FinishingZone == nullptr)
    {
        PRINT_ONSCREEN_WARN("No FinishingZone can be found. Please add one to the level!");
    }

    BP_ScanLevelForData();
}

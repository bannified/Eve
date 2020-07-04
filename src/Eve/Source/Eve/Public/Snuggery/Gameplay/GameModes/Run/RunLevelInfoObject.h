// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EveCore/LevelInfoObjectBase.h"
#include "RunLevelInfoObject.generated.h"

class AStartingZone;
class AFinishingZone;

/**
 * 
 */
UCLASS()
class EVE_API ARunLevelInfoObject : public ALevelInfoObjectBase
{
	GENERATED_BODY()

public:
    virtual void ScanLevelForData() override;

    FORCEINLINE AStartingZone* GetStartingZone() { return StartingZone; }
    FORCEINLINE AFinishingZone* GetFinishingZone() { return FinishingZone; }

protected:
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Run|LevelInfo", meta = (AllowPrivateAccess))
    AStartingZone* StartingZone;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Run|LevelInfo", meta = (AllowPrivateAccess))
    AFinishingZone* FinishingZone;
};

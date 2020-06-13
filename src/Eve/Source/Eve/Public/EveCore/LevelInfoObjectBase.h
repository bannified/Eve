// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "LevelInfoObjectBase.generated.h"

/**
 * A LevelInfoObject is an object that lives in the level at Editor-time.
 * This is a dedicated place that stores information about the level, such as Spawn Points.
 * Tackles the problem of GameMode not being able to access specific information about the level 
 * without GetAllActorsOfClass (which is inefficient) at runtime.
 */
UCLASS(Blueprintable, Abstract)
class EVE_API ALevelInfoObjectBase : public AInfo
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Level")
    virtual void ScanLevelForData();

    UFUNCTION(BlueprintImplementableEvent, Category = "Level")
    void BP_ScanLevelForData();
};

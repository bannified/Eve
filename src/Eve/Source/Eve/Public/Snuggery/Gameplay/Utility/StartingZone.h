// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Delegates/Delegate.h"
#include "StartingZone.generated.h"

class USceneComponent;
class UDecalComponent;
class UStaticMeshComponent;
class UTextRenderComponent;

UCLASS()
class EVE_API AStartingZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStartingZone();

    UFUNCTION(BlueprintCallable, Category = "StartingZone")
    void ActivateZoneBoundary();
    UFUNCTION(BlueprintCallable, Category = "StartingZone")
    void DeactivateZoneBoundary();

protected:
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

    // Components

    // Root Component
    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "StartingZone")
    USceneComponent* StartingZoneRootComponent;

    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "StartingZone")
    USceneComponent* VisualComponent;
    
    // Parent SceneComponent of Floor decal group
    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category="StartingZone")
    USceneComponent* DecalGroup;

    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "StartingZone")
    UDecalComponent* FloorDecalComponent;

    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "StartingZone")
    UStaticMeshComponent* DecalPlane;

    // Collider actual
    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "StartingZone")
    UStaticMeshComponent* ZoneCollider;

    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "StartingZone")
    UTextRenderComponent* DebugTextRenderComponent;

    void UpdateZoneColliderBox();

};

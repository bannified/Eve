// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrippableLedge.generated.h"

class UStaticMeshComponent;
class UArrowComponent;

UCLASS()
class EVE_API AGrippableLedge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrippableLedge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "GrippableLedge")
    UStaticMeshComponent* LedgeCollider;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "GrippableLedge")
    UArrowComponent* DirectionalArrow;

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable,  Category = "GrippableLedge")
    FVector GetUnitDirectionVectorToPosition(FVector position);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

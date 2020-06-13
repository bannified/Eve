// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishingZone.generated.h"

class UBoxComponent;
class USceneComponent;
class UPrimitiveComponent;
class ASnuggeryCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSimpleOverlapSignature, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerEnterZoneSignature, ASnuggeryCharacter*, snuggeryCharacter);

UCLASS()
class EVE_API AFinishingZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFinishingZone();

protected:
    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "FinishingZone")
    UBoxComponent* BoxTrigger;

    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "FinishingZone")
    USceneComponent* VisualComponent;

    UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "FinishingZone")
    FSimpleOverlapSignature OnBeginOverlapZone;

    UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "FinishingZone")
    FPlayerEnterZoneSignature OnPlayerEnterZone;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UFUNCTION(BlueprintImplementableEvent, Category = "FinishingZone")
    void BP_OnComponentBeginOverlapZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp);

    UFUNCTION(Category = "FinishingZone")
    virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

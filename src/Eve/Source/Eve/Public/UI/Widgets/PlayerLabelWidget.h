// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerLabelWidget.generated.h"

class UCameraComponent;
class ASnuggeryCharacterBase;

/**
 * 
 */
UCLASS()
class EVE_API UPlayerLabelWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UPlayerLabelWidget(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, Category = "PlayerLabelWidget")
    void SetupWithPlayer(ASnuggeryCharacterBase* snuggeryCharacter);

protected:
    UFUNCTION(BlueprintCallable, Category = "PlayerLabelWidget")
    void UpdateName(const FString& newName);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerLabelWidget")
    FString PlayerName;

    UFUNCTION(BlueprintImplementableEvent, Category = "PlayerLabelWidget")
    void BP_OnPlayerNameUpdate();

    /* Distance-based scaling of name labels */

    /* The character this label belongs to */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerLabelWidget")
    ASnuggeryCharacterBase* OwnerCharacter;

    /* The camera of the local player */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerLabelWidget")
    UCameraComponent* LocalPlayerCamera;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerLabelWidget")
    float MaxScale;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerLabelWidget")
    float MinScale;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerLabelWidget")
    float LabelScaleNearPlaneDistanceSq;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerLabelWidget")
    float LabelScaleFarPlaneDistanceSq;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerLabelWidget")
    float DistanceSqDelta;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerLabelWidget")
    UCurveFloat* ScaleCurve;

    virtual void NativeOnInitialized() override;

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Snuggery/SnuggeryCharacterBase.h"
#include "SnuggeryCharacter.generated.h"

class ASnuggeryPlayerController;
class ASnuggeryPetCharacter;
class USnuggeryCharacterDataAsset;
class ASnuggeryPlayerState;

class UCameraComponent;
class USpringArmComponent;
class UWidgetComponent;
class UParticleSystem;

UENUM(BlueprintType, Category = "SnuggeryCharacter")
enum ESnuggeryCharacterCameraMode {
    PlayerPivot, // MMO-style camera panning
    Platformer,
    ThirdPerson, // 
};

UCLASS()
class EVE_API ASnuggeryCharacter : public ASnuggeryCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASnuggeryCharacter();

    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

protected:
    /* Camera */
    UPROPERTY(EditAnywhere, Category = "SnuggeryCharacter|Camera")
    TEnumAsByte<ESnuggeryCharacterCameraMode> CameraMode;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryCharacter|Camera", meta = (AllowPrivateAccess = "true"))
    bool bCameraPanEnabled;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SnuggeryCharacter|Camera", meta = (AllowPrivateAccess = "true"))
    bool bIsPlayerPanning;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryCharacter|Camera", meta = (AllowPrivateAccess = "true"))
    float CameraHorizontalPanSpeed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryCharacter|Camera", meta = (AllowPrivateAccess = "true"))
    float CameraVerticalPanSpeed;

    /* Pets */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SnuggeryCharacter|Pets", meta = (AllowPrivateAccess = "true"))
    ASnuggeryPetCharacter* CurrentPet;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryCharacter|Pets", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<ASnuggeryPetCharacter> StarterPetClass;

public:
    /* Movement interface */
    virtual void OnMoveRight(float inScale) override;

    virtual void OnMoveForward(float inScale) override;

    virtual void OnJumpStart() override;
    virtual void OnJumpEnd() override;

    /* Look */
    virtual void OnLookRight(float inScale) override;
    virtual void OnLookUp(float inScale) override;

    /* Camera Pan */
    virtual void OnCameraPanStart() override;
    virtual void OnCameraPanEnd() override;

    /* Camera */
    UFUNCTION(BlueprintCallable, Category = "SnuggeryCharacter|Camera")
    void SetupCameraMode(TEnumAsByte<ESnuggeryCharacterCameraMode> mode);

    /* Chat Feature */
protected:

    //void SetChatAvatarImage(const )

    virtual void PlaySpawnEffect() override;

    UFUNCTION(BlueprintCallable, Server, Reliable, Category = "SnuggeryCharacter|Chat")
    void SendMessage(const FString& message);

public:
    UFUNCTION(BlueprintCallable, Client, Reliable, Category = "SnuggeryCharacter|Chat")
    void ReceiveMessage(ASnuggeryPlayerState* sender, const FString& message);

    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter|Chat")
    void OnMessageReceived(ASnuggeryPlayerState* sender, const FString& message);

    /* Character Customization and Switching */
    virtual void SwitchCharacter_Server(USnuggeryCharacterDataAsset* characterData) override;

    virtual void SwitchCharacter_Multicast(USnuggeryCharacterDataAsset* characterData) override;

    /* ACharacter overrides */
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

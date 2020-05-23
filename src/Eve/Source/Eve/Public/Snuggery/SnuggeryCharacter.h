// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SnuggeryCharacter.generated.h"

class ASnuggeryPlayerController;

class UCameraComponent;
class USpringArmComponent;
class UWidgetComponent;
class ASnuggeryPlayerState;
class UParticleSystem;
class USnuggeryCharacterDataAsset;

UENUM(BlueprintType, Category = "SnuggeryCharacter")
enum ESnuggeryCharacterCameraMode {
    PlayerPivot, // MMO-style camera panning
    Platformer,
    ThirdPerson, // 
};

UCLASS()
class EVE_API ASnuggeryCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASnuggeryCharacter();

    virtual void OnPossessedByPlayerController(ASnuggeryPlayerController* playerController);

    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

protected:
    /* Chat */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SnuggeryCharacter|Chat", meta = (AllowPrivateAccess = "true"))
    UWidgetComponent* NameLabelWidgetComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SnuggeryCharacter|Chat", meta = (AllowPrivateAccess = "true"))
    UWidgetComponent* ChatBubbleWidgetComponent;

    /* Effects */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryCharacter|Effects", meta = (AllowPrivateAccess = "true"))
    UParticleSystem* SpawnParticleSystem;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryCharacter|Effects", meta = (AllowPrivateAccess = "true"))
    FVector SpawnParticleScale;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SnuggeryCharacter|Camera", meta = (AllowPrivateAccess = "true"))
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SnuggeryCharacter|Camera", meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* SpringArmComponent;

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

public:
    /* Movement interface */
    virtual void OnMoveRight(float inScale);

    virtual void OnMoveForward(float inScale);

    virtual void OnJumpStart();
    virtual void OnJumpEnd();

    /* Look */
    virtual void OnLookRight(float inScale);
    virtual void OnLookUp(float inScale);

    /* Camera Pan */
    virtual void OnCameraPanStart();
    virtual void OnCameraPanEnd();

    /* Camera */
    UFUNCTION(BlueprintCallable, Category = "SnuggeryCharacter|Camera")
    void SetupCameraMode(TEnumAsByte<ESnuggeryCharacterCameraMode> mode);

    /* Effects */
    UFUNCTION(BlueprintCallable, Category = "SnuggeryCharacter|Effect")
    void PlaySpawnEffect();

    /* Character Customization and Switching */
    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "SnuggeryCharacter|CharacterCustomization")
    void SwitchCharacter_Server(USnuggeryCharacterDataAsset* characterData);

    UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "SnuggeryCharacter|CharacterCustomization")
    void SwitchCharacter_Multicast(USnuggeryCharacterDataAsset* characterData);

protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter")
    void BP_OnSwitchCharacter(USnuggeryCharacterDataAsset* characterData);    

    /* Blueprint-Implementables */
protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter")
    void BP_OnJumpStart();    
    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter")
    void BP_OnJumpEnd();

    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter")
    void BP_OnMoveRight(float inScale);

    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter")
    void BP_OnMoveForward(float inScale);

    /* Chat Feature */
protected:

    //void SetChatAvatarImage(const )

    UFUNCTION(BlueprintCallable, Server, Reliable, Category = "SnuggeryCharacter|Chat")
    void SendMessage(const FString& message);

public:
    UFUNCTION(BlueprintCallable, Client, Reliable, Category = "SnuggeryCharacter|Chat")
    void ReceiveMessage(ASnuggeryPlayerState* sender, const FString& message);

    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter|Chat")
    void OnMessageReceived(ASnuggeryPlayerState* sender, const FString& message);

    /* ACharacter overrides */
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

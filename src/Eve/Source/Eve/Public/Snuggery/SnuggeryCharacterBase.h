// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SnuggeryCharacterBase.generated.h"

class ASnuggeryPlayerController;

class UCameraComponent;
class USpringArmComponent;
class UWidgetComponent;
class ASnuggeryPlayerState;
class UParticleSystem;
class USnuggeryCharacterDataAsset;

UCLASS()
class EVE_API ASnuggeryCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASnuggeryCharacterBase();

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;

    virtual void OnPossessedByPlayerController(ASnuggeryPlayerController* playerController);

    virtual void PossessedBy(AController* NewController) override;

    virtual void OnRep_PlayerState() override;

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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

    /* Effects */
    UFUNCTION(BlueprintCallable, Category = "SnuggeryCharacter|Effect")
    virtual void PlaySpawnEffect();

    /* Character Customization and Switching */
    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "SnuggeryCharacter|CharacterCustomization")
    virtual void SwitchCharacter_Server(USnuggeryCharacterDataAsset* characterData);

    UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "SnuggeryCharacter|CharacterCustomization")
    virtual void SwitchCharacter_Multicast(USnuggeryCharacterDataAsset* characterData);

protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter")
    void BP_OnSwitchCharacter(USnuggeryCharacterDataAsset* characterData);    

    /* Blueprint-Implementables */
protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter")
    void BP_OnMoveRight(float inScale);
    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter")
    void BP_OnMoveForward(float inScale);

    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter")
    void BP_OnJumpStart();    
    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter")
    void BP_OnJumpEnd();

    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter")
    void BP_OnLookRight(float inScale);    
    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter")
    void BP_OnLookUp(float inScale);

    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter")
    void BP_OnCameraPanStart();    
    UFUNCTION(BlueprintImplementableEvent, Category = "SnuggeryCharacter")
    void BP_OnCameraPanEnd();
};

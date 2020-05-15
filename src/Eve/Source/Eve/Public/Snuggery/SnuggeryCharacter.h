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

UCLASS()
class EVE_API ASnuggeryCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASnuggeryCharacter();

    virtual void OnPossessedByPlayerController(ASnuggeryPlayerController* playerController);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* SpringArmComponent;

    /* Chat */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SnuggeryCharacter", meta = (AllowPrivateAccess = "true"))
    UWidgetComponent* NameLabelWidgetComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SnuggeryCharacter", meta = (AllowPrivateAccess = "true"))
    UWidgetComponent* ChatBubbleWidgetComponent;

    /* Effects */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryCharacter|Effects", meta = (AllowPrivateAccess = "true"))
    UParticleSystem* SpawnParticleSystem;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryCharacter|Effects", meta = (AllowPrivateAccess = "true"))
    FVector SpawnParticleScale;

public:
    /* Movement interface */
    virtual void OnMoveRight(float inScale);

    virtual void OnMoveForward(float inScale);

    virtual void OnJumpStart();
    virtual void OnJumpEnd();

    /* Effects */
    UFUNCTION(BlueprintCallable, Category = "SnuggeryCharacter|Effect")
    void PlaySpawnEffect();

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

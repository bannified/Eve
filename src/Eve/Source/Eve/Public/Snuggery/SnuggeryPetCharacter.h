// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Snuggery/SnuggeryCharacterBase.h"
#include "SnuggeryPetCharacter.generated.h"

class UBehaviorTree;
class ASnuggeryCharacter;

/**
 * 
 */
UCLASS()
class EVE_API ASnuggeryPetCharacter : public ASnuggeryCharacterBase
{
	GENERATED_BODY()
	
public:
    ASnuggeryPetCharacter();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryPetCharacter")
    UBehaviorTree* BehaviorTree;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryPetCharacter")
    FName MinFollowUntilDistance_BBKey;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryPetCharacter")
    float MinFollowUntilDistance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryPetCharacter")
    FName MaxFollowUntilDistance_BBKey;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryPetCharacter")
    float MaxFollowUntilDistance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryPetCharacter")
    FName StartFollowDistance_BBKey;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryPetCharacter")
    float StartFollowDistance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SnuggeryPetCharacter")
    FName OwnerCharacter_BBKey;

    virtual void PossessedBy(AController* NewController) override;

    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "SnuggeryPetCharacter")
    virtual void SetPetOwner_Server(ASnuggeryCharacter* character);

    UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "SnuggeryPetCharacter")
    virtual void SetPetOwner_Multicast(ASnuggeryCharacter* character);

};

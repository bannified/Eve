// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/SnuggeryPetCharacter.h"
#include "GameFramework/Controller.h"
#include "AIController.h"
#include "Snuggery/SnuggeryCharacter.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"

ASnuggeryPetCharacter::ASnuggeryPetCharacter() : ASnuggeryCharacterBase()
{
    MinFollowUntilDistance_BBKey = "MinFollowUntilDistance";
    MinFollowUntilDistance = 125.0f;
    MaxFollowUntilDistance_BBKey = "MaxFollowUntilDistance";
    MaxFollowUntilDistance = 175.0f;

    StartFollowDistance_BBKey = "StartFollowDistance";
    StartFollowDistance = 350.0f;

    OwnerCharacter_BBKey = "OwnerCharacter";
}

void ASnuggeryPetCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    AAIController* casted = Cast<AAIController>(NewController);

    if (casted == nullptr)
    {
        return;
    }

    casted->RunBehaviorTree(BehaviorTree);
    UBlackboardComponent* blackboard = casted->GetBlackboardComponent();

    blackboard->SetValueAsFloat(MinFollowUntilDistance_BBKey, MinFollowUntilDistance);
    blackboard->SetValueAsFloat(MaxFollowUntilDistance_BBKey, MaxFollowUntilDistance);
    blackboard->SetValueAsFloat(StartFollowDistance_BBKey, StartFollowDistance);
}

void ASnuggeryPetCharacter::SetPetOwner_Multicast_Implementation(ASnuggeryCharacter* character)
{
    SetPetOwner_Multicast(character);
}

void ASnuggeryPetCharacter::SetPetOwner_Server_Implementation(ASnuggeryCharacter* character)
{
    AAIController* casted = Cast<AAIController>(GetController());

    if (casted == nullptr)
    {
        return;
    }

    UBlackboardComponent* blackboard = casted->GetBlackboardComponent();

    blackboard->SetValueAsObject(OwnerCharacter_BBKey, character);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/DataAssets/SnuggeryCharacterDataAsset.h"
#include "Snuggery/SnuggeryCharacterBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimBlueprint.h"

void USnuggeryCharacterDataAsset::InitializeCharacter(ASnuggeryCharacterBase* character)
{
    character->GetMesh()->SetSkeletalMesh(SkeletalMesh);
    character->GetMesh()->SetAnimInstanceClass(AnimationBlueprint->GeneratedClass);

    K2_InitializeCharacter(character);
}

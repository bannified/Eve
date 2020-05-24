// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/SnuggeryCharacterBase.h"

// Sets default values
ASnuggeryCharacterBase::ASnuggeryCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASnuggeryCharacterBase::OnPossessedByPlayerController(ASnuggeryPlayerController* playerController)
{

}

// Called when the game starts or when spawned
void ASnuggeryCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASnuggeryCharacterBase::OnMoveRight(float inScale)
{
    BP_OnMoveRight(inScale);
}

void ASnuggeryCharacterBase::OnMoveForward(float inScale)
{
    BP_OnMoveForward(inScale);
}

void ASnuggeryCharacterBase::OnJumpStart()
{
    BP_OnJumpStart();
}

void ASnuggeryCharacterBase::OnJumpEnd()
{
    BP_OnJumpEnd();
}

void ASnuggeryCharacterBase::OnLookRight(float inScale)
{
    BP_OnLookRight(inScale);
}

void ASnuggeryCharacterBase::OnLookUp(float inScale)
{
    BP_OnLookUp(inScale);
}

void ASnuggeryCharacterBase::OnCameraPanStart()
{
    BP_OnCameraPanStart();
}

void ASnuggeryCharacterBase::OnCameraPanEnd()
{
    BP_OnCameraPanEnd();
}

void ASnuggeryCharacterBase::PlaySpawnEffect()
{

}

void ASnuggeryCharacterBase::SwitchCharacter_Multicast_Implementation(USnuggeryCharacterDataAsset* characterData)
{
    BP_OnSwitchCharacter(characterData);
}

void ASnuggeryCharacterBase::SwitchCharacter_Server_Implementation(USnuggeryCharacterDataAsset* characterData)
{
    SwitchCharacter_Multicast(characterData);
}


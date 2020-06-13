// Fill out your copyright notice in the Description page of Project Settings.


#include "Snuggery/SnuggeryGameState.h"
#include "Snuggery/DataAssets/SnuggeryCharacterDataAsset.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "HAL/FileManagerGeneric.h"
#include "UObject/ConstructorHelpers.h"
#include "EditorAssetLibrary.h"
#include "Engine/ObjectLibrary.h"

void ASnuggeryGameState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

ASnuggeryGameState::ASnuggeryGameState()
{

}

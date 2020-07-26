// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widgets/SnuggeryPlayerUI.h"
#include "SnuggeryHUD.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class EVE_API ASnuggeryHUD : public AHUD
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    // Todo: Add in WBP_SnuggeryPlayer and WBP_CharacterSelection
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "SnuggeryHUD")
    TSubclassOf<USnuggeryPlayerUI> PlayerUIClass;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SnuggeryHUD")
    USnuggeryPlayerUI* PlayerUIWidget;

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "SnuggeryHUD")
    TSubclassOf<UUserWidget> CharacterSelectionClass;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SnuggeryHUD")
    UUserWidget* CharacterSelectionWidget;

public:
    UFUNCTION(BlueprintCallable, Category = "SnuggeryHUD")
    virtual void StartGameStartCountdown(float timeToStartGame);

    virtual void OnPlayerStateInitialized();

    FORCEINLINE UChatboxWidget* GetChatboxWidget() { return PlayerUIWidget->GetChatboxWidget(); }
};

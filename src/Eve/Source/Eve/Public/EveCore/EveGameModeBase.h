// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EveGameModeBase.generated.h"

class AGameModeState;
class APlayerState;

UCLASS(minimalapi)
class AEveGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
	AEveGameModeBase();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EveGameModeBase|State Machine")
	AGameModeState* SavedState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EveGameModeBase|State Machine")
	AGameModeState* CurrentState;

    /**
	 * State Machine
	 */
	UFUNCTION(BlueprintCallable, Category = "MemGameModeBase|State Machine")
	void MoveToState(AGameModeState* NextState);

	//UFUNCTION(BlueprintCallable, Category = "MemGameModeBase|Lifecycle")
	//virtual void StartGame(ULevelDataAsset* LevelData);

	UFUNCTION(BlueprintCallable, Category = "EveGameModeBase|Gameplay Flow")
	void WinGame();

	UFUNCTION(BlueprintCallable, Category = "EveGameModeBase|Gameplay Flow")
	void LoseGame();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "EveGameModeBase|Gameflow")
    void BP_WinGame();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "EveGameModeBase|Gameflow")
    void BP_LoseGame();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "EveGameModeBase|Gameflow")
    void BP_OnStateChanged(AGameModeState* oldState, AGameModeState* newState);
    
    virtual void PostLogin(APlayerController* NewPlayer) override;

    virtual void ChangeName(AController* Controller, const FString& NewName, bool bNameChange) override;

    void RegisterPlayerState(APlayerState* playerState);

    // An alternative to OnPostLogin, because this is only called only after a player's PlayerState and GameState have been replicated.
    virtual void OnPlayerFullyInitialized(APlayerState* playerState);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "EveGameModeBase|Player Management")
	TArray<APlayerController*> PlayerControllerList;

	UFUNCTION(BlueprintCallable, Category = "EveGameModeBase|Player Management")
	virtual void RegisterPlayer(APlayerController* playerController);

    UFUNCTION(BlueprintCallable, Category = "EveGameModeBase|Constants")
    const FString GetPlayerNameFormat() const { return s_DefaultPlayerNameFormatString; };

    static inline const TCHAR* const GetDefaultPlayerNameFormat() { return s_DefaultPlayerNameFormat; };

    static const FString s_DefaultPlayerNameFormatString;
    static const TCHAR* s_DefaultPlayerNameFormat;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "EveGameModeBase")
    float CurrentTime;

    UFUNCTION(BlueprintCallable, Category = "EveGameModeBase")
    void ResetCurrentTime();

    UPROPERTY(BlueprintReadOnly, Category = "EveGameModeBase")
    TSet<APlayerState*> InitializedPlayerStates;

};




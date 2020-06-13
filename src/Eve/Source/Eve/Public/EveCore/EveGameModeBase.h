// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EveGameModeBase.generated.h"

class AGameModeState;

UCLASS(minimalapi)
class AEveGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEveGameModeBase();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MemGameModeBase|State Machine")
	AGameModeState* SavedState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MemGameModeBase|State Machine")
	AGameModeState* CurrentState;

    /**
	 * State Machine
	 */
	UFUNCTION(BlueprintCallable, Category = "MemGameModeBase|State Machine")
	void MoveToState(AGameModeState* NextState);

	//UFUNCTION(BlueprintCallable, Category = "MemGameModeBase|Lifecycle")
	//virtual void StartGame(ULevelDataAsset* LevelData);

	UFUNCTION(BlueprintCallable, Category = "MemGameModeBase|Gameplay Flow")
	void WinGame();

	UFUNCTION(BlueprintCallable, Category = "MemGameModeBase|Gameplay Flow")
	void LoseGame();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "MemGameModeBase|Gameflow")
    void BP_WinGame();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "MemGameModeBase|Gameflow")
    void BP_LoseGame();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "MemGameModeBase|Gameflow")
    void BP_OnStateChanged(AGameModeState* oldState, AGameModeState* newState);
    
    virtual void PostLogin(APlayerController* NewPlayer) override;

    virtual void ChangeName(AController* Controller, const FString& NewName, bool bNameChange) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "MemGameModeBase|Player Management")
	TArray<APlayerController*> PlayerControllerList;

	UFUNCTION(BlueprintCallable, Category = "MemGameModeBase|Player Management")
	virtual void RegisterPlayer(APlayerController* playerController);

    UFUNCTION(BlueprintCallable, Category = "MemGameModeBase|Constants")
    const FString GetPlayerNameFormat() const { return s_DefaultPlayerNameFormatString; };

    static inline const TCHAR* const GetDefaultPlayerNameFormat() { return s_DefaultPlayerNameFormat; };

    static const FString s_DefaultPlayerNameFormatString;
    static const TCHAR* s_DefaultPlayerNameFormat;
};




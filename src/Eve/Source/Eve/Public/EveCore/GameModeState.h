// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "GameModeState.generated.h"

class AEveGameModeBase;

/**
 * 
 */
UCLASS()
class EVE_API AGameModeState : public AInfo
{
	GENERATED_BODY()
	
private:
    AGameModeState();

public:
    AGameModeState(AEveGameModeBase* GameMode);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
    AEveGameModeBase* GameMode;

	UFUNCTION(BlueprintCallable, Category = "Game Mode State")
	virtual void Init();

	/**
	 * Called when the GameMode enters this state.
	 */
	UFUNCTION(BlueprintCallable, Category = "Game Mode State")
	virtual void OnStateEnter();

	/**
	 * Called whenever this states starts executing.
	 * Therefore, this method is called even when the GameMode is resumed (but still in this state).
	 */
	UFUNCTION(BlueprintCallable, Category = "Game Mode State")
	virtual void OnStateStart();

	/**
	 * Called every tick when this GameMode is active with this state.
	 */
	UFUNCTION(BlueprintCallable, Category = "Game Mode State")
	virtual void OnStateTick(const float DeltaTime);

	/**
	 * Called when state stops.
	 * Therefore, this method is called even when the GameMode is paused (but still in this state).
	 */
	UFUNCTION(BlueprintCallable, Category = "Game Mode State")
	virtual void OnStateStop();

	/**
	 * Called when GameMode exits this state.
	 */
	UFUNCTION(BlueprintCallable, Category = "Game Mode State")
	virtual void OnStateExit();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Game Mode State")
	void BP_OnStateEnter();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Game Mode State")
	void BP_OnStateStart();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Game Mode State")
	void BP_OnStateTick(const float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Game Mode State")
	void BP_OnStateStop();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Game Mode State")
	void BP_OnStateExit();
};

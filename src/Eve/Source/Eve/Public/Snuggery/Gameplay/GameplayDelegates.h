#pragma once

#include "CoreMinimal.h"
#include "GameplayDelegates.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNameChangeSignature, const FString&, newName);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameEndSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStartSignature);


UCLASS(abstract)
class EVE_API UGameplayDelegates : public UObject {
    GENERATED_BODY()
};

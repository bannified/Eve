// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "Engine/GameEngine.h"

DECLARE_LOG_CATEGORY_EXTERN(LogEve, Log, All);

#define CUSTOM_MOVEMENT_CLIMB 1

#define OBJECT_TYPE_TRAVERSAL ECC_GameTraceChannel1
#define OBJECT_TYPE_CHARACTER_TRAVERSAL ECC_GameTraceChannel2

#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
#define PRINT_ONSCREEN_INFO(...) if(GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::Printf(TEXT(__VA_ARGS__))); }
#define PRINT_ONSCREEN_WARN(...) if(GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT(__VA_ARGS__))); }
#define PRINT_WARN(...) UE_LOG(LogEve, Warning, TEXT(__VA_ARGS__))
#else
#define PRINT_ONSCREEN_INFO(x)
#endif

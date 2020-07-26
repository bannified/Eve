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

#define NETMODE_WORLD_TEXT (((GEngine == nullptr) || (GetWorld() == nullptr)) ? TEXT("") \
        : (GEngine->GetNetMode(GetWorld()) == NM_Client) ? TEXT("[Client] ") \
        : (GEngine->GetNetMode(GetWorld()) == NM_ListenServer) ? TEXT("[ListenServer] ") \
        : (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer) ? TEXT("[DedicatedServer] ") \
        : TEXT("[Standalone] "))

#if _MSC_VER
#define FUNC_NAME    TEXT(__FUNCTION__)
#else // FIXME - GCC?
#define FUNC_NAME    TEXT(__func__)
#endif

#define TRACE_INFO(Format, ...) \
{ \
    SET_WARN_COLOR(COLOR_WHITE);\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    UE_LOG(LogEve, Log, TEXT("%s%s() : %s, %s"), NETMODE_WORLD_TEXT, FUNC_NAME, *GetNameSafe(this), *Msg);\
    CLEAR_WARN_COLOR();\
}

#define TRACE_SPECIAL(Format, ...) \
{ \
    SET_WARN_COLOR(COLOR_CYAN);\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    UE_LOG(LogEve, Log, TEXT("%s%s() : %s, %s"), NETMODE_WORLD_TEXT, FUNC_NAME, *GetNameSafe(this), *Msg);\
    CLEAR_WARN_COLOR();\
}

#define TRACE_STATIC(Format, ...) \
{ \
    SET_WARN_COLOR(COLOR_CYAN);\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    UE_LOG(LogEve, Log, TEXT("%s() : %s"), FUNC_NAME, *Msg);\
    CLEAR_WARN_COLOR();\
}

#define TRACE_WARN(Format, ...) \
{ \
    SET_WARN_COLOR( COLOR_YELLOW );\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    UE_LOG(LogEve, Warning, TEXT("**WARNING** %s%s() : %s, %s"), NETMODE_WORLD_TEXT, FUNC_NAME, *GetNameSafe(this), *Msg);\
    CLEAR_WARN_COLOR();\
}

#define TRACE_ERROR(Format, ...) \
{ \
    SET_WARN_COLOR( COLOR_RED );\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    UE_LOG(LogEve, Error, TEXT("**ERROR** %s%s() : %s, %s"), NETMODE_WORLD_TEXT, FUNC_NAME, *GetNameSafe(this), *Msg);\
    CLEAR_WARN_COLOR();\
}

#define SCREENDEBUG(Format, ...) \
{ \
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    TCHAR ResultMsg[MAX_SPRINTF] = TEXT(""); \
    FCString::Sprintf(ResultMsg, TEXT("%s%s() : %s, %s"), NETMODE_WORLD_TEXT, FUNC_NAME, *GetNameSafe(this), *Msg); \
    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, ResultMsg); \
}
#else
#define PRINT_ONSCREEN_INFO(x)
#define TRACE(Format, ...)
#define TRACESTATIC(Format, ...)
#define TRACEWARN(Format, ...)
#define TRACEERROR(Format, ...)
#define SCREENDEBUG(Format, ...)
#endif

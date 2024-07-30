// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

#pragma region Log

 // 유틸리티 함수 정의
inline FString GetCleanFilename(const char* FilePath)
{
	FString FilePathStr = FString(ANSI_TO_TCHAR(FilePath)).Replace(TEXT("\\"), TEXT("/"));
	int32 LastSlashIndex;
	if (FilePathStr.FindLastChar('/', LastSlashIndex))
	{
		return FilePathStr.RightChop(LastSlashIndex + 1);
	}
	return FilePathStr;
}

#define __FILENAME__ (GetCleanFilename(__FILE__))


#if UE_BUILD_SHIPPING
// Shipping에서는 출력을 무시할 log
#define LOG_V(Fmt, ...)
#define WAR_V(Fmt, ...)
#define LOG_I
#define LOG_GUARD
#define LOG_GUARD_STR(str)
#else

#define LOG_E(msg)		UE_LOG(LogTemp, Log, TEXT("[LOG] %s", msg))
#define LOG_V(Fmt, ...) UE_LOG(LogTemp, Log, TEXT("[LOG][%s::%s(%d)] " Fmt), *__FILENAME__, TEXT(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#define WAR_V(Fmt, ...) UE_LOG(LogTemp, Warning, TEXT("[WAR][%s::%s(%d)] " Fmt), *__FILENAME__, TEXT(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#define LOG_I			UE_LOG(LogTemp, Log, TEXT("[LOG][%s::%s(%d)]"), *__FILENAME__, TEXT(__FUNCTION__), __LINE__)

#define LOG_GUARD			FLogGuard logGuard(__FILENAME__ + ANSI_TO_TCHAR(__FUNCTION__))
#define LOG_GUARD_STR(str)	FLogGuard logGuard(__FILENAME__ + FString(TEXT("::")) + FString(ANSI_TO_TCHAR(__FUNCTION__)) + str)

#endif

#define SCREEN_LOG_V(Fmt, ...) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("[LOG][%s::%s(%d)] " Fmt), *__FILENAME__, TEXT(__FUNCTION__), __LINE__, ##__VA_ARGS__))
#define SCREEN_WAR_V(Fmt, ...) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("[WAR][%s::%s(%d)] " Fmt), *__FILENAME__, TEXT(__FUNCTION__), __LINE__, ##__VA_ARGS__))
#define SCREEN_ERR_V(Fmt, ...) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("[ERR][%s::%s(%d)] " Fmt), *__FILENAME__, TEXT(__FUNCTION__), __LINE__, ##__VA_ARGS__))

#define ERR_V(Fmt, ...) UE_LOG(LogTemp, Error, TEXT("[ERR][%s::%s(%d)] " Fmt), *__FILENAME__, TEXT(__FUNCTION__), __LINE__, ##__VA_ARGS__)


// FLogGuard 구조체 정의
struct FLogGuard
{
	FLogGuard(FString InStr)
		: FunctionName(InStr)
	{
		// 함수 시작 로그 출력
		UE_LOG(LogTemp, Log, TEXT("[Start][%s]"), *FunctionName);
	}

	// 소멸자: 함수의 끝 로그를 출력합니다.
	~FLogGuard()
	{
		UE_LOG(LogTemp, Log, TEXT("[End][%s]"), *FunctionName);
	}

private:
	FString FunctionName; // 함수 이름을 저장하는 변수
};

#pragma endregion
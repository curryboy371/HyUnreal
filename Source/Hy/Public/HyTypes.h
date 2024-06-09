// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HyTypes.generated.h" // GENERATED_BODY() 매크로를 사용하기 위해 필요
/**
 *
 */

#pragma region Define

#define UE_PROJECT 1

#pragma endregion


#pragma region Struct



struct HY_API FPacketHeader
{
	FPacketHeader()
		: PacketSize(0), PacketID(0)
	{

	}

	FPacketHeader(uint16 InPacketSize, uint16 InPacketID)
		: PacketSize(InPacketSize), PacketID(InPacketID)
	{

	}

	friend FArchive& operator<<(FArchive& Ar, FPacketHeader& Header)
	{
		Ar << Header.PacketSize;
		Ar << Header.PacketID;
		return Ar;
	}

	uint16 PacketSize;
	uint16 PacketID;
};


class SendBuffer : public TSharedFromThis<SendBuffer>
{
public:
	SendBuffer(int32 bufferSize);
	~SendBuffer();

	BYTE* Buffer() { return _buffer.GetData(); }
	int32 WriteSize() { return _writeSize; }
	int32 Capacity() { return static_cast<int32>(_buffer.Num()); }

	void CopyData(void* data, int32 len);
	void Close(uint32 writeSize);

private:
	TArray<BYTE>	_buffer;
	int32			_writeSize = 0;
};

USTRUCT(BlueprintType)
struct FCharacterMoveOption
{
    GENERATED_BODY()


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character MoveOption")
    float MaxWalkSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character MoveOption")
    float MaxAcceleration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character MoveOption")
    float BrakingDeceleration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character MoveOption")
    float BrakingFrictionFactor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character MoveOption")
    float BrakingFriction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character MoveOption")
	bool UseSeparateBrakingFriction;

	// 생성자
	FCharacterMoveOption()
		: MaxWalkSpeed(0.f)
		, MaxAcceleration(0.f)
		, BrakingDeceleration(0.f)
		, BrakingFrictionFactor(0.f)
		, BrakingFriction(0.f)
		, UseSeparateBrakingFriction(false)
	{
	}

};

#pragma endregion


#pragma region Enum

UENUM(BlueprintType)
enum class ELocomotionDirection : uint8
{
	Forward					UMETA(DisplayName = "Forward Direction"),
	ForwardRight			UMETA(DisplayName = "ForwardRight Direction"),
	ForwardLeft				UMETA(DisplayName = "ForwardLeft Direction"),
	Backward				UMETA(DisplayName = "Backward Direction"),
	BackwardRight			UMETA(DisplayName = "BackwardRight Direction"),
	BackwardLeft			UMETA(DisplayName = "BackwardLeft Direction"),
	Right					UMETA(DisplayName = "Right Direction"),
	Left					UMETA(DisplayName = "Left Direction"),
};



UENUM(BlueprintType)
enum class EEquippedWeaponState : uint8
{
	UnArmed			UMETA(DisplayName = "UnArmed Equipped"),
	Rifle			UMETA(DisplayName = "Rifle Equipped"),
	Pistol			UMETA(DisplayName = "Pistol Equipped"),
};


UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle			UMETA(DisplayName = "Idle State"),
	Walking			UMETA(DisplayName = "Walking State"),
	Jogging			UMETA(DisplayName = "Jogging State"),
};


UENUM(BlueprintType)
enum class EManagerNum : uint8
{
	Network    UMETA(DisplayName = "Network Manager"),
	Max        UMETA(DisplayName = "Max Manager")
};

#pragma endregion


#pragma region Utils

 // macro
#define USING_SHARED_PTR(name)	using name##Ref = TSharedPtr<class name>;
USING_SHARED_PTR(HySession);
USING_SHARED_PTR(PacketSession);
USING_SHARED_PTR(SendBuffer);

#pragma endregion


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

		UE_LOG(LogTemp, Log, TEXT("Recv PacketID : %d, PacketSize : %d"), 1,2);

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

#pragma region GetterSetter

#define GETTER(type, name) \
public: \
    const type& Get_##name##_Ref() const { return name; } \
	type Get_##name() const { return name; } \
private:

#define SETTER(type, name) \
public: \
    void Set_##name(const type& value) { name = value; } \
private:

#pragma endregion


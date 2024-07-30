// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "Protocol.pb.h"
#include "UObject/NoExportTypes.h"
#include "Kismet/GameplayStatics.h"


#include "TimerManager.h"
#include "Engine/World.h"

#include "Engine/DataTable.h"
#include "GameplayTagContainer.h" // FGameplayTag
#include "Game/HyDeveloperSettings.h"

#include "HyTypes.generated.h" // GENERATED_BODY() 매크로를 사용하기 위해 필요
/**
 *
 */
extern class UHyGameInstance* GGameInstance;

#pragma region Define

#define UE_PROJECT 1

#pragma endregion


#pragma region Struct

struct FUserInfo
{
	// hyps_user_info
	FUserInfo()
	{
		UserID = 0;
		UserName = TEXT("");
		UserType = Protocol::hype_user::user_none;
	}

	int64 UserID;
	FString UserName;
	Protocol::hype_user UserType;
};

struct FObjectSpawnInfo
{
	// hyps_pos_info
	// hyps_object_info
	FObjectSpawnInfo()
	{
		ObjectID = 0;
		Location = FVector::Zero();
		Rotation = FRotator::ZeroRotator;
		ObjectType = Protocol::hype_object_type::none;
	}

	int64 ObjectID;
	FVector Location;
	FRotator Rotation;
	Protocol::hype_object_type ObjectType;
};




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

UENUM()
enum class EMoveMode : uint8
{
	EWalk UMETA(DisplayName = "Walk"),
	ERun UMETA(DisplayName = "Run"),
	ESprint UMETA(DisplayName = "ESprint"),
	EDash UMETA(DisplayName = "Dash"),
	EEvade UMETA(DisplayName = "Evade")
};


UENUM(BlueprintType)
enum class EControlPlayer : uint8
{
	ENoneControl UMETA(DisplayName = "NoneControl"),
	EPlayer1 UMETA(DisplayName = "Player1"),
	EPlayer2 UMETA(DisplayName = "Player2"),
	EPlayer3 UMETA(DisplayName = "Player3")
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
	Time	    UMETA(DisplayName = "Time Manager"),
	Spawn	    UMETA(DisplayName = "Spawn Manager"),
	Data		UMETA(DisplayName = "Data Manager"),
	Network		UMETA(DisplayName = "Network Manager"),
	Max			UMETA(DisplayName = "Max Manager")
};

#pragma endregion



#pragma region Struct

// Common

USTRUCT(BlueprintType)
struct FHyStruct {

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HY)
	FGameplayTag TagName;


	FORCEINLINE bool operator!=(const FGameplayTag& Other) const
	{
		return TagName != Other;
	}

	FORCEINLINE bool operator==(const FGameplayTag& Other) const
	{
		return TagName == Other;
	}

	FORCEINLINE bool operator!=(const FHyStruct& Other) const
	{
		return TagName != Other.TagName;
	}

	FORCEINLINE bool operator==(const FHyStruct& Other) const
	{
		return TagName == Other.TagName;
	}
};

class UNiagaraSystem;
class USoundBase;

USTRUCT(BlueprintType)
struct FBaseFX : public FTableRowBase
{
	GENERATED_BODY()

public:
	FBaseFX()
	{
		ActionSound = nullptr;
		NiagaraParticle = nullptr;
		PSParticle = nullptr;
	}

	FBaseFX(TObjectPtr<USoundBase> inSound, TObjectPtr<UNiagaraSystem> inNSParticle, TObjectPtr<UParticleSystem> inPSParticle)
	{
		ActionSound = inSound;
		NiagaraParticle = inNSParticle;
		PSParticle = inPSParticle;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX)
	TObjectPtr<USoundBase> ActionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX)
	TObjectPtr<UNiagaraSystem> NiagaraParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX)
	TObjectPtr<UParticleSystem> PSParticle;
};



#pragma region Utils

 // macro
#define USING_SHARED_PTR(name)	using name##Ref = TSharedPtr<class name>;
USING_SHARED_PTR(HySession);
USING_SHARED_PTR(PacketSession);
USING_SHARED_PTR(SendBuffer);

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


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HyTypes.h"

#include "GameFramework/DamageType.h" // UDagageType

#include "HyFXTypes.generated.h"

/**
 * 
 */


 ///////////////////////////////
 // 
 // 
 // 
 // Effect Sound
// effect
USTRUCT(BlueprintType)
struct FEffectByDamageType : public FHyStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NP)
		TMap<TSubclassOf<UDamageType>, FBaseFX> EffectByDamageType;
};

/// Effect Sound Enum
UENUM(BlueprintType)
enum class ESpawnFXLocation : uint8
{
	ESpawnOnActorLocation UMETA(DisplayName = "Attached to Actor"),
	ESpawnAttachedToSocketOrBone UMETA(DisplayName = "Attached to Socket / Bone"),
	ESpawnAtLocation UMETA(DisplayName = "Spawn On Provided Tranform")
};


USTRUCT(BlueprintType)
struct FHyActionEffect : public FBaseFX {
	GENERATED_BODY()

public:
	FHyActionEffect()
		:SpawnLocation(ESpawnFXLocation::ESpawnOnActorLocation), Guid(0, 0, 0, 0)
	{
		ActionSound = nullptr;
		NiagaraParticle = nullptr;
	}

	FHyActionEffect(const FBaseFX& baseFX, const ESpawnFXLocation inLocationType, const FName& inName)
		:Guid(0,0,0,0)
	{
		ActionSound = baseFX.ActionSound;
		NiagaraParticle = baseFX.NiagaraParticle;
		SpawnLocation = inLocationType;
		SocketOrBoneName = inName;
		
	}

	FGuid GetGuid() const 	{ return Guid; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX)
	FName SocketOrBoneName = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX)
	ESpawnFXLocation SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX)
	float NoiseEmitted = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX)
	FTransform RelativeOffset;

private:
	UPROPERTY()
	FGuid Guid;
};

USTRUCT(BlueprintType)
struct FDispatchFX : public FBaseFX {
	GENERATED_BODY()

public:
	FDispatchFX()
	{
		ActionSound = nullptr;
		NiagaraParticle = nullptr;
		SpawnLocation = FTransform();
	}

	FDispatchFX(const FBaseFX& baseFX, const FVector& location)
	{
		ActionSound = baseFX.ActionSound;
		NiagaraParticle = baseFX.NiagaraParticle;
		SpawnLocation = FTransform(location);
	}

	FDispatchFX(const FHyActionEffect& baseFX, const FTransform& location)
	{
		ActionSound = baseFX.ActionSound;
		NiagaraParticle = baseFX.NiagaraParticle;
		SpawnLocation = location;
	}

	FDispatchFX(const FDispatchFX& baseFX)
	{
		ActionSound = baseFX.ActionSound;
		NiagaraParticle = baseFX.NiagaraParticle;
		SpawnLocation = baseFX.SpawnLocation;
	}

	UPROPERTY(BlueprintReadWrite, Category = NP)
		FTransform SpawnLocation;
};

USTRUCT(BlueprintType)
struct FAttachedComponents 
{
	GENERATED_BODY()

public:
	FAttachedComponents()
	{
		NiagaraComp = nullptr;
		AudioComp = nullptr;
		CascadeComp = nullptr;
	}

	UPROPERTY()
	TObjectPtr<UParticleSystemComponent> CascadeComp;

	UPROPERTY()
	TObjectPtr<class UNiagaraComponent> NiagaraComp;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AudioComp;
};





// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DamageEvents.h"
#include "Components/SphereComponent.h"
#include "HyGameplayTags.h"
#include "HyCombatTypes.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class EHitCase : uint8
{
    EHitCase_Single UMETA(DisplayName = "Single Hit"),
    EHitCase_Multi UMETA(DisplayName = "Multi Hit"),
};


UENUM(BlueprintType)
enum class ECombatDirection : uint8
{
    EForward UMETA(DisplayName = "Forward"),
    ERight UMETA(DisplayName = "Right"),
    ELeft UMETA(DisplayName = "Left"),
    EBack UMETA(DisplayName = "Back"),
    EForwardRight UMETA(DisplayName = "ForwardRight"),
    EForwardLeft UMETA(DisplayName = "ForwardLeft"),
    EBackRight UMETA(DisplayName = "BackRight"),
    EBackLeft UMETA(DisplayName = "BackLeft"),
    EDirectionMax UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAIMoveType : uint8
{
    EAIMove_None UMETA(DisplayName = "EAIMove_None"),
    EAIMove_Random UMETA(DisplayName = "EAIMove_Random"),
    EAIMove_Follow UMETA(DisplayName = "EAIMove_Follow"),
    EAIMove_Target UMETA(DisplayName = "EAIMove_Target"),
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
    EDamage_Normal UMETA(DisplayName = "Normal Damage"),
    EDamage_Critical UMETA(DisplayName = "Critical Damage"),
    EDamage_Miss UMETA(DisplayName = "Miss Damage"),
};

UENUM(BlueprintType)
enum class EPPMType : uint8
{
    EPPM_Stencil    UMETA(DisplayName = "EPPM_Stencil"),
    EPPM_Blur       UMETA(DisplayName = "EPPM_Blur"),
    EPPM_Scan       UMETA(DisplayName = "EPPM_Scan"),
    EPPM_Test       UMETA(DisplayName = "EPPM_Test"),
    EPPM_MAX        UMETA(DisplayName = "EPPM_MAX"),
};



USTRUCT()
struct FHyDamageEvent : public FDamageEvent
{
    GENERATED_BODY()

        FHyDamageEvent()
        : HitTag(FGameplayTag::EmptyTag)
    { }

    virtual ~FHyDamageEvent() { }


	/** ID for this class. NOTE this must be unique for all damage events. */
	static const int32 ClassID = 3;

	virtual int32 GetTypeID() const override { return FHyDamageEvent::ClassID; };
	virtual bool IsOfType(int32 InID) const override { return (FHyDamageEvent::ClassID == InID) || FDamageEvent::IsOfType(InID); };

    UPROPERTY()
    FGameplayTag HitTag;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HyTypes.h"
#include "FX/HyFXTypes.h"
#include "NativeGameplayTags.h"

#include "RootMotionModifier.h"


#include "HyActionTypes.generated.h"

/**
 
 About ActionSystem struct...


 */


// Actio 종료 타입
UENUM(BlueprintType)
enum class EActionHandleExitType : uint8
{
    EActionExit_Free UMETA(DisplayName = "EActionExit_Free"), // StoreAction 실행 > 진행중이던 Action 종료
    EActionExit_Stop UMETA(DisplayName = "EActionExit_Stop"), // 진행중이던 Action 즉시 Stop Exit > StoreAction 실행
    EActionExit_Conditional UMETA(DisplayName = "EActionExit_Conditional"), // 각 Action의 조건 실행, 조건이 참이면 Stop ( 조건반환을 항상 false로 하고 조건함수 안에서 Handle하기도 함 )
};

// action 우선순위
UENUM(BlueprintType)
enum class EActionPriority : uint8 {
    ENone UMETA(DisplayName = "Very Low"),
    ELow UMETA(DisplayName = "Low"),
    EMedium UMETA(DisplayName = "Medium"),
    EHigh UMETA(DisplayName = "High"),
    EHighest UMETA(DisplayName = "Highest"),
};

// Montage BlendType 타입
UENUM(BlueprintType)
enum class EMontageBlendType : uint8 {
    // 블랜드 사용 안함
    EMontageBlend_None UMETA(DisplayName = "EMontageBlend_None"),

    // 시작시에만 블렌드 사용
    EMontageBlend_Start UMETA(DisplayName = "EMontageBlend_Start"),

    // 끝났을시에만 블렌드 사용
    EMontageBlend_End UMETA(DisplayName = "EMontageBlend_End"),

    // 시작, 종료 모두 블렌드
    EMontageBlend_Both UMETA(DisplayName = "EMontageBlend_Both"),
};



UENUM(BlueprintType)
enum class EMontageReproductionType : uint8 
{
    ERootMotion UMETA(DisplayName = "Root Motion"),
    ERootMotionScaled UMETA(DisplayName = "Root Motion Scaled"),
    EMotionWarped UMETA(DisplayName = "Root Motion Warped"),
    ECurveOverrideSpeed UMETA(DisplayName = "Override Speed with Curve_DEPRECATED"),
    ECurveSnapsOnTarget UMETA(DisplayName = "Override Speed and Snaps To Target_DEPRECATED"),
    ECurveOverrideSpeedAndDirection UMETA(DisplayName = "Override Speed and Direction Vector_DEPRECATED"),
};

UENUM(BlueprintType)
enum class EWarpTargetType : uint8 {
    ETargetTransform UMETA(DisplayName = "Target Transform"),
    ETargetComponent UMETA(DisplayName = "Target Component"),
};


USTRUCT(BlueprintType)
struct FHyWarpInfo 
{

    GENERATED_USTRUCT_BODY()
public:
    FHyWarpInfo()
        :RotationType(EMotionWarpRotationType::Default), TargetType(EWarpTargetType::ETargetTransform)
    {
        WarpStartTime = 0.f;
        bIgnoreZAxis = true;
        WarpEndTime = 1.f;
        WarpRotationTime = 1.f;
        SyncPoint = "Target";
        bAutoWarp = true;
    }

    /*Turn this off if you want to use the anim notify instead*/
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = HY)
    bool bAutoWarp;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = HY)
    FName SyncPoint;

    UPROPERTY(BlueprintReadWrite, meta = (EditCondition = "bAutoWarp == true"), EditDefaultsOnly, Category = HY)
    float WarpStartTime;

    UPROPERTY(BlueprintReadWrite, meta = (EditCondition = "bAutoWarp == true"), EditDefaultsOnly, Category = HY)
    float WarpEndTime;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = HY)
    float WarpRotationTime;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = HY)
    bool bIgnoreZAxis;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = HY)
    EMotionWarpRotationType RotationType;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = HY)
    EWarpTargetType TargetType;

    UPROPERTY(BlueprintReadWrite, meta = (EditCondition = "TargetType == EWarpTargetType::ETargetComponent"), EditDefaultsOnly, Category = HY)
    bool bMagneticFollow = true;

    UPROPERTY(EditDefaultsOnly, Category = HY)
    bool bShowWarpDebug = false;
};

USTRUCT(BlueprintType)
struct FHyWarpReproductionInfo {

    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = HY)
    FHyWarpInfo WarpConfig;

    UPROPERTY(BlueprintReadWrite, Category = HY)
    FVector WarpLocation;

    UPROPERTY(BlueprintReadWrite, Category = HY)
    FRotator WarpRotation;

    UPROPERTY(BlueprintReadWrite, Category = HY)
    USceneComponent* TargetComponent;

    FHyWarpReproductionInfo()
    {
        TargetComponent = nullptr;
        WarpConfig = FHyWarpInfo();
        WarpLocation = FVector(0.f);
        WarpRotation = FRotator(0.f);
    }
};

USTRUCT(BlueprintType)
struct FHyActionConfig {
    GENERATED_BODY()

public:
    FHyActionConfig()
    {
        MontageReproductionType = EMontageReproductionType::ERootMotion;
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HYAnimConfig)
    bool bPlayEffectOnActionStart = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HYAnimConfig)
    FHyActionEffect ActionEffect;

    // if true action montage play, false not play
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HYAnimConfig)
    bool bAutoExecute = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HYAnimConfig)
    EMontageReproductionType MontageReproductionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "MontageReproductionType == EMontageReproductionType::ERootMotionScaled"), Category = HYAnimConfig)
    float RootMotionScale = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HYAnimConfig)
    EMontageBlendType MontageBlend = EMontageBlendType::EMontageBlend_Both;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "MontageReproductionType == EMontageReproductionType::EMotionWarped"), Category = HYAnimConfig)
    FHyWarpInfo WarpInfo;
};



USTRUCT(BlueprintType)
struct FHyActionState : public FHyStruct 
{
    GENERATED_BODY()

    FHyActionState()
    {
        MontageAction = nullptr;
        Action = nullptr;
    };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Action")
    TObjectPtr<class UAnimMontage> MontageAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Hy | Action")
    TObjectPtr<class UHyActionBase> Action;
};

USTRUCT(BlueprintType)
struct FHyActionsSet : public FHyStruct 
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hy | Action")
    TSubclassOf<class UHyActionsDataAsset> ActionsSet;
};


USTRUCT(BlueprintType)
struct FHyMontageInfo 
{
    GENERATED_USTRUCT_BODY()
public:
    FHyMontageInfo(class UAnimMontage* inAnimMontage)
        :ReproductionType(EMontageReproductionType::ERootMotion), RootMotionScale(1.f)
    {
        MontageAction = inAnimMontage;
        ReproductionSpeed = 1.f;
        StartSectionName = NAME_None;
    }

    FHyMontageInfo()
        :ReproductionType(EMontageReproductionType::ERootMotion), RootMotionScale(1.f)
    {
        MontageAction = nullptr;
        ReproductionSpeed = 1.f;
        StartSectionName = NAME_None;
    }

    UPROPERTY(BlueprintReadWrite, Category = HY)
    TObjectPtr<class UAnimMontage> MontageAction;

    UPROPERTY(BlueprintReadWrite, Category = HY)
    EMontageBlendType MontageBlend = EMontageBlendType::EMontageBlend_Both;

    UPROPERTY(BlueprintReadWrite, Category = HY)
    float ReproductionSpeed;

    UPROPERTY(BlueprintReadWrite, Category = HY)
    FName StartSectionName;

    UPROPERTY(BlueprintReadWrite, Category = HY)
    EMontageReproductionType ReproductionType;

    UPROPERTY(BlueprintReadWrite, meta = (EditCondition = "MontageReproductionType == EMontageReproductionType::ERootMotionScaled"), Category = HY)
    float RootMotionScale;

    UPROPERTY(BlueprintReadWrite, meta = (EditCondition = "MontageReproductionType == EMontageReproductionType::EMotionWarped"), Category = HY)
    FHyWarpReproductionInfo WarpInfo;
};

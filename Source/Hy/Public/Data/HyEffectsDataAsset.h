// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Hy.h"
#include "FX/HyFXTypes.h"
#include "GameplayTagContainer.h" // FGameplayTag

#include "HyEffectsDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyEffectsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
    bool GetDamageEffects(const FGameplayTag& HitReaction,
        const TSubclassOf<UDamageType>& damageType, FBaseFX& outFX)
    {
        FEffectByDamageType* effectList = nullptr;
        if (HitReaction == FGameplayTag::EmptyTag) {
           // effectList = DamageEffectsByHitReaction.FindByKey(UNPFunctionLibrary::GetDefaultHitState());
        }
        else {
           // effectList = DamageEffectsByHitReaction.FindByKey(HitReaction);
        }

        if (!effectList) {
            return false;
        }

        if (effectList->EffectByDamageType.Contains(damageType)) {
            outFX = *effectList->EffectByDamageType.Find(damageType);
            return true;
        }
        else {
            for (auto& currentDam : effectList->EffectByDamageType) {
                if (damageType->IsChildOf(currentDam.Key)) {
                    outFX = currentDam.Value;
                    return true;
                }
            }
        }

        return false;
    }
public:
    // 데미지를 받을때 표시할 효과, 위치는 충돌지점.
    UPROPERTY(BlueprintReadOnly, meta = (TitleProperty = "TagName"), EditDefaultsOnly, Category = "Hy | Damages")
    TArray<FEffectByDamageType> DamageEffectsByHitReaction;
	
};

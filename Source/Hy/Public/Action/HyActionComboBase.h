// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyActionBase.h"
#include "HyActionComboBase.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyActionComboBase : public UHyActionBase
{
	GENERATED_BODY()
	
public:

    UFUNCTION(BlueprintPure, Category = HY)
    FORCEINLINE int32 GetComboCounter() const { return CurrentComboIndex; }

    UFUNCTION(BlueprintPure, Category = HY)
    FORCEINLINE bool IsSuccessfulCombo() const { return bSuccesfulCombo; }
	
	UFUNCTION(BlueprintCallable, Category = HY)
    void ResetComboCounter()
    {
        CurrentComboIndex = 0;
    }

    UFUNCTION(BlueprintCallable, Category = HY)
    void ForceComboCounter(int32 val)
    {
        CurrentComboIndex = val;
    }
	
protected:
    virtual void OnActionStarted_Implementation(const FString& contextString = "") override;

    virtual void OnTick_Implementation(float DeltaTime);

    virtual FName GetMontageSectionName_Implementation() override;

    virtual void OnActionEnded_Implementation() override;

    virtual void OnActionTransition_Implementation(class UHyActionBase* previousState) override;

    virtual void ClearActionState();

    int32 CurrentComboIndex = 0;

    bool bSuccesfulCombo = false;

    float CheckInterval = 0.1f;
    float AttackReadyRatio = 0.5f;
    float LastCheckTime = 0.0f;


    float Test = 0.0f;

};

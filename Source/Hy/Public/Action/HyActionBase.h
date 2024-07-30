// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HyActionTypes.h"
#include "HyActionBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class HY_API UHyActionBase : public UObject
{
	GENERATED_BODY()

public:
    /*Called when the action is successfully triggered*/
    UFUNCTION(BlueprintNativeEvent, Category = HY)
    void OnActionStarted(const FString& contextString = "");
    virtual void OnActionStarted_Implementation(const FString& contextString = "") {};


    /*Called when the action montage setup completed*/
    UFUNCTION(BlueprintNativeEvent, Category = HY)
    void OnActionSetupCompleted(const FString& contextString = "");
    virtual void OnActionSetupCompleted_Implementation(const FString& contextString = "") {};

    /*Called when the action is finished. Normally if BindActionToAnimation is set to true
    this is called when the animation is finished*/
    UFUNCTION(BlueprintNativeEvent, Category = HY)
    void OnActionEnded();
    virtual void OnActionEnded_Implementation() {};

    /*Called when the action is successfully triggered and BEFORE the OnActionStarted.
    If the character is coming from the DefaultState previousState will be nullptr*/
    UFUNCTION(BlueprintNativeEvent, Category = HY)
    void OnActionTransition(class UHyActionBase* previousState);
    virtual void OnActionTransition_Implementation(class UHyActionBase* previousState) {};

    /*Called every frame if the ActionsManagerComponent of this character has bCanTick set to true*/
    UFUNCTION(BlueprintNativeEvent, Category = HY)
    void OnTick(float DeltaTime);
    virtual void OnTick_Implementation(float DeltaTime) {};


    UFUNCTION(BlueprintNativeEvent, Category = HY)
    bool IsStopConditional();
    virtual bool IsStopConditional_Implementation() { return true; };


    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = HY)
    void PlayEffects();
    virtual void PlayEffects_Implementation();

    /*Implement this to configure the warp info. Only called if MontageReproductionType is set to Warp */
    UFUNCTION(BlueprintNativeEvent, Category = HY)
    void GetWarpInfo(FHyWarpReproductionInfo& outWarpInfo);
    virtual void GetWarpInfo_Implementation(FHyWarpReproductionInfo& outWarpInfo);

    /*Implement this if you only want to configure the transform of the warp point.
    Only called if MontageReproductionType is set to Warp */
    UFUNCTION(BlueprintNativeEvent, Category = HY)
    FTransform GetWarpTransform();
    virtual FTransform GetWarpTransform_Implementation();

    /*Implement this if you only want to configure the transform of the warp point.
    Only called if MontageReproductionType is set to Warp */
    UFUNCTION(BlueprintNativeEvent, Category = HY)
    USceneComponent* GetWarpTargetComponent();
    virtual USceneComponent* GetWarpTargetComponent_Implementation();

    /*Implement this to select the name of the montage section that should be played when executing this action */
    UFUNCTION(BlueprintNativeEvent, Category = HY)
    FName GetMontageSectionName();
    virtual FName GetMontageSectionName_Implementation() { return NAME_None; };


    /*Implement this to select the name of the montage section that should be played when executing this action */
    UFUNCTION(BlueprintCallable, Category = HY)
    void SetMontageInfo(const FHyMontageInfo& montageInfo) {};

    /*Interrupt current action AND animation Immediately*/
    UFUNCTION(BlueprintCallable, Category = HY)
    void StopActionImmediately() {};



    UFUNCTION(BlueprintNativeEvent, Category = HY)
    float GetPlayRate();
    virtual float GetPlayRate_Implementation() { return AnimRate; };
    void SetAnimRate(float Rate) {AnimRate = Rate;}

    /*Play the animation montage related to this action. Called automatically by default*/
    UFUNCTION(BlueprintCallable, Category = HY)
    void ExecuteAction();

    /*Called to force the end of the action. Does not stop the animation but allows the trigger of eventually stored
    actions or set the actual state to the default one*/
    UFUNCTION(BlueprintCallable, Category = HY)
    void ExitAction();

    virtual void Internal_OnActivated(TObjectPtr<class UHyActionSetComponent> actionsetCom, TObjectPtr<class UAnimMontage> inAnimMontage, const FString& contextString);
    virtual void Internal_OnDeactivated();

    virtual void ClearActionState() {};

    void PrepareMontageInfo();

    void BindMontageEvents();
    void UnbindMontageEvents();

    bool GetMontageProgress(float& OutPregress);

    int32 GetCurMontageSectionIdx();
    int32 GetCurMontageSectionLength();

    UFUNCTION()
    void HandleMontageFinished(class UAnimMontage* InAnimMontage, bool InbInterruptted);

    UFUNCTION()
    void HandleMontageStarted(class UAnimMontage* InAnimMontage);

    bool GetTerminated() const { return bTerminated; }
    void SetTerminated(bool val) { bTerminated = val; }


public:
    const FHyActionConfig& GetActionConfig() { return ActionConfig; }

    TObjectPtr<class AHyCharacter> GetCharacterOwner() { return CharacterOwner; }
    void SetCharacterOwner(TObjectPtr<class AHyCharacter> InOwner) { CharacterOwner = InOwner; }

    UFUNCTION(BlueprintPure, Category = HY)
    FGameplayTag GetActionTag() const { return ActionTag ; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = HY)
    TObjectPtr<class UHyActionSetComponent> ActionSetCom;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HY)
    FHyActionConfig ActionConfig;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HY)
    bool bBindMontageEvent = true; // true is Montage Animation event Bind

    UPROPERTY(BlueprintReadOnly, Category = HY)
    TObjectPtr<class AHyCharacter> CharacterOwner;

    UPROPERTY(BlueprintReadOnly, Category = HY)
    TObjectPtr<class UAnimMontage> animMontage;

    UPROPERTY(BlueprintReadWrite, Category = HY)
    FHyMontageInfo MontageInfo;

    UPROPERTY(BlueprintReadOnly, Category = HY)
    FGameplayTag ActionTag;

    bool bIsExecutingAction = false;

    bool bTerminated = false;

    float AnimRate = 1.0f;
    float StartFrame = 0.0f;

    float ElapsedTime = 0.0f;
    float DeltaTimeInterval = 0.2f;
};

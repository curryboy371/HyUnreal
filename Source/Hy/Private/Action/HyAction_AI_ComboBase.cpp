// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AI_ComboBase.h"
#include "Character/HyCharacter.h"

#include "AI/HyAIController.h"
#include "HyTypes.h"
#include "Game/HyDeveloperSettings.h"
#include "HyGameplayTags.h"

void UHyAction_AI_ComboBase::OnActionStarted_Implementation(const FString& contextString)
{
	bSuccesfulCombo = false;
	Super::OnActionStarted_Implementation();

	CheckInterval = 0.1f;
	AttackReadyRatio = 0.25f;
	LastCheckTime = 0.0f;
}

void UHyAction_AI_ComboBase::OnTick_Implementation(float DeltaTime)
{
    if (!CharacterOwner)
    {
        return;
    }

    LastCheckTime += DeltaTime;


    if (LastCheckTime > CheckInterval)
    {
        if (HyAIController)
        {
            HyAIController->SetBBValue<bool>(FName("bCanAttack"), true);
        }
        LastCheckTime = 0.0f;
    }
}

FName UHyAction_AI_ComboBase::GetMontageSectionName_Implementation()
{
    if (animMontage)
    {
        const FName SectionName = animMontage->GetSectionName(CurrentComboIndex);

        if (SectionName != NAME_None)
        {
            return SectionName;
        }
        else
        {
            CurrentComboIndex = 0;
            return animMontage->GetSectionName(CurrentComboIndex);
        }
    }
    return NAME_None;
}

void UHyAction_AI_ComboBase::OnActionEnded_Implementation()
{
    Super::OnActionEnded_Implementation();

    // 콤보 실패시 초기화
    if (!bSuccesfulCombo)
    {
        CurrentComboIndex = 0;

        if (HyAIController)
        {
            HyAIController->SetBBValue<bool>(FName("bCanAttack"), true);
        }
    }
}

void UHyAction_AI_ComboBase::OnActionTransition_Implementation(UHyActionBase* previousState)
{
    Super::OnActionTransition_Implementation(previousState);

    if (previousState && previousState->IsA(GetClass()))
    {
        if (animMontage && CurrentComboIndex > animMontage->CompositeSections.Num())
        {
            CurrentComboIndex = 0;
        }
        else
        {
            CurrentComboIndex++;
        }
        bSuccesfulCombo = true;
    }
    else
    {
        CurrentComboIndex = 0;
        bSuccesfulCombo = false;
    }

    //LOG_V("CurrentComboIndex %d", CurrentComboIndex);
}

void UHyAction_AI_ComboBase::ClearActionState()
{
    CurrentComboIndex = 0;
    bSuccesfulCombo = false;
}

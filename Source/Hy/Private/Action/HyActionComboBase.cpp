// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyActionComboBase.h"

#include "Character/HyCharacter.h"
#include "HyGameplayTags.h"

void UHyActionComboBase::OnActionStarted_Implementation(const FString& contextString)
{
	bSuccesfulCombo = false;
	Super::OnActionStarted_Implementation();

    CheckInterval = 0.1f;
    AttackReadyRatio = 0.25f;
    LastCheckTime = 0.0f;
}

void UHyActionComboBase::OnTick_Implementation(float DeltaTime)
{
    if (!CharacterOwner)
    {
        return;
    }

    LastCheckTime += DeltaTime;

    Test += DeltaTime;

    //if (LastCheckTime > CheckInterval)
    //{
    //    if (CharacterOwner->GetCanAttack() == false)
    //    {
    //        CharacterOwner->ResetCanAttack();
    //    }
    //
    //    LastCheckTime = 0.0f;
    //}

    LOG_V("ComboIndex %d %f", CurrentComboIndex, Test);
}

FName UHyActionComboBase::GetMontageSectionName_Implementation()
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

void UHyActionComboBase::OnActionEnded_Implementation()
{
    Super::OnActionEnded_Implementation();

    // 콤보 실패시 초기화
    if (!bSuccesfulCombo) 
    {
        CurrentComboIndex = 0;
        //if(CharacterOwner)
        //{
        //    CharacterOwner->ResetCanAttack();
        //}

        Test = 0.0f;

    }
}

void UHyActionComboBase::OnActionTransition_Implementation(UHyActionBase* previousState)
{
    Super::OnActionTransition_Implementation(previousState);

    if (previousState && previousState->IsA(GetClass())) 
    {
        if (animMontage && CurrentComboIndex > animMontage->CompositeSections.Num()) 
        {
            CurrentComboIndex = 0;
            Test = 0.0f;
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
        Test = 0.0f;


        // 콤보어택 최초 시작시 AttackDash 이후라면 Startindex 1부터
        // AttackDash에 첫 공격이 포함되었기 때문
        if (previousState)
        {
            if (FHyTags::Get().ActionAttackDash == previousState->GetActionTag())
            {
                CurrentComboIndex = 1;
            }
        }
    }
}

void UHyActionComboBase::ClearActionState()
{
    CurrentComboIndex = 0;
    bSuccesfulCombo = false;
}

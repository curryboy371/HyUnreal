// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyActionBase.h"

#include "Action/HyActionComboBase.h"
#include "Components/HyActionSetComponent.h"
#include "Character/HyCharacter.h"
#include "Elements/Columns/TypedElementRevisionControlColumns.h"

#include "Game/HyGameInstance.h"
#include "FX/HyFXDispatcher.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Animation/AnimMontage.h"


void UHyActionBase::ExecuteAction()
{
    if (animMontage && ActionSetCom) 
    {
        if (bBindMontageEvent) 
        {
            BindMontageEvents();
        }

        PrepareMontageInfo(); // Action에 있는 몽타주 정보를 MontageInfo에 Set
        ActionSetCom->PlayMontage(MontageInfo, StartFrame);
        bIsExecutingAction = true;
    }
    else 
    {
        ExitAction();
    }
}

void UHyActionBase::ExitAction()
{
    if (ActionSetCom)
    {
        if (ActionSetCom->IsEmptyStoredAction())
        {
            ActionSetCom->SetDefaultStoredActionTag();
        }

        ActionSetCom->InternalExitAction();
    }
}

void UHyActionBase::Internal_OnActivated(TObjectPtr<UHyActionSetComponent> actionsetCom, TObjectPtr<UAnimMontage> inAnimMontage, const FString& contextString)
{
    ActionSetCom = actionsetCom;
    animMontage = inAnimMontage;
    if (ActionSetCom)
    {

        CharacterOwner = ActionSetCom->CharacterOwner;
        ActionTag = ActionSetCom->CurrentActionTag;
    }

    // Pre AnimationSet
    OnActionStarted(contextString);

    // Action에 설정된 몽타주를 실행
    if (ActionConfig.bAutoExecute)
    {
        ExecuteAction();
    }

    // Completed AnimationSet
    OnActionSetupCompleted(contextString);
}

void UHyActionBase::Internal_OnDeactivated()
{
    if (bIsExecutingAction) 
    {
        bIsExecutingAction = false;
    }

    OnActionEnded();
}

void UHyActionBase::PrepareMontageInfo()
{
    MontageInfo.MontageAction = animMontage;
    MontageInfo.MontageBlend = ActionConfig.MontageBlend;
    MontageInfo.ReproductionSpeed = GetPlayRate();
    MontageInfo.StartSectionName = GetMontageSectionName();

    MontageInfo.ReproductionType = ActionConfig.MontageReproductionType;
    MontageInfo.RootMotionScale = 1.f;
    MontageInfo.RootMotionScale = 1.f;

    FHyWarpReproductionInfo outWarp;

    //UMotionWarpingComponent* motionComp = CharacterOwner->FindComponentByClass<UMotionWarpingComponent>();

    switch (MontageInfo.ReproductionType) {
    case EMontageReproductionType::ERootMotionScaled:
        MontageInfo.RootMotionScale = ActionConfig.RootMotionScale;
        break;
    case EMontageReproductionType::ERootMotion:
        break;
    case EMontageReproductionType::EMotionWarped:
        //if (motionComp) {
        //    GetWarpInfo(outWarp);
        //    MontageInfo.WarpInfo = outWarp;
        //}
        break;
    }
}

void UHyActionBase::BindMontageEvents()
{
    if (CharacterOwner) 
    {
        UAnimInstance* animinst = (CharacterOwner->GetMesh()->GetAnimInstance());
        if (animinst) 
        {
            animinst->OnMontageStarted.AddDynamic(this, &UHyActionBase::HandleMontageStarted);
        }
    }
}

void UHyActionBase::UnbindMontageEvents()
{
    if (CharacterOwner)
    {
        UAnimInstance* animinst = (CharacterOwner->GetMesh()->GetAnimInstance());

        if (animinst)
        {
            animinst->OnMontageStarted.RemoveDynamic(this, &UHyActionBase::HandleMontageStarted);
            animinst->OnMontageEnded.RemoveDynamic(this, &UHyActionBase::HandleMontageFinished);
        }
    }
}

bool UHyActionBase::GetMontageProgress(float& OutPregress)
{
	// 하나의 몽타주 섹션에서만 사용되도록 변경 ( 임시 ) 
    // 몽타주는 섹션 순서대로 진행된다는 가정하에 사용
    // 재생중인 몽타주 비율 반환
    if (MontageInfo.MontageAction && CharacterOwner)
    {
        if (UAnimInstance* animinst = (CharacterOwner->GetMesh()->GetAnimInstance()))
        {
            // 현재까지 진행된 섹션의 길이
            //float MontageLength = 0.0f;
            //int32 CurSectionIdx = MontageInfo.MontageAction->GetSectionIndex(GetMontageSectionName());
            //CurSectionIdx = FMath::Clamp(CurSectionIdx, 0, CurSectionIdx);
            //
            //for (int32 i = 0; i <= CurSectionIdx; ++i)
            //{
            //    MontageLength += MontageInfo.MontageAction->GetSectionLength(CurSectionIdx);
            //}
            if (animinst->Montage_IsPlaying(MontageInfo.MontageAction))
            {
                float CurrentTime = animinst->Montage_GetPosition(MontageInfo.MontageAction);
                OutPregress = CurrentTime;
                return true;
            }

            //LOG_V("CurrentTime %f  MontageLength %f", CurrentTime, MontageLength);
            //
            //if (MontageLength > 0.f)
            //{
            //    OutPregress = CurrentTime / MontageLength;
            //    return true;
            //}
        }
    }
    return false;
}

int32 UHyActionBase::GetCurMontageSectionIdx()
{
    int32 CurSectionIndex = 0;
    if (MontageInfo.MontageAction && CharacterOwner)
    {
        CurSectionIndex = MontageInfo.MontageAction->GetSectionIndex(GetMontageSectionName());
        CurSectionIndex = FMath::Clamp(CurSectionIndex, 0, CurSectionIndex);
    }


    return CurSectionIndex;
}

int32 UHyActionBase::GetCurMontageSectionLength()
{
    int32 MaxSectionIndex = 0;
    if (MontageInfo.MontageAction && CharacterOwner)
    {
        MaxSectionIndex = MontageInfo.MontageAction->CompositeSections.Num();
    }

    return MaxSectionIndex;

}

void UHyActionBase::HandleMontageFinished(class UAnimMontage* InAnimMontage, bool InbInterruptted)
{
    if (animMontage == InAnimMontage && bIsExecutingAction && !InbInterruptted)
    {
        ExitAction();
    }
}

void UHyActionBase::HandleMontageStarted(class UAnimMontage* InAnimMontage)
{
    UAnimInstance* animinst = (CharacterOwner->GetMesh()->GetAnimInstance());

    UnbindMontageEvents();

    if (animinst)
    {
        // Bind
        if (animMontage == InAnimMontage) 
        {
            animinst->OnMontageEnded.AddDynamic(this, &UHyActionBase::HandleMontageFinished);
        }
    }
}

void UHyActionBase::PlayEffects_Implementation()
{
    UHyGameInstance* HyGameInstance = Cast<UHyGameInstance>(GWorld->GetGameInstance());
    if (HyGameInstance)
    {
        if (TObjectPtr<UHyFXDispatcher> FXDispatcher = HyGameInstance->GetFXDispatcher())
        {
            FXDispatcher->PlayActionFX(ActionConfig.ActionEffect, CharacterOwner);
        }
    }
}

void UHyActionBase::GetWarpInfo_Implementation(FHyWarpReproductionInfo& outWarpInfo)
{
    outWarpInfo.WarpConfig = ActionConfig.WarpInfo;
    //  float sectionStart, sectionEnd;
    const FName sectionName = GetMontageSectionName();
    int32 currentIndex = animMontage->GetSectionIndex(sectionName);
    if (currentIndex < 0) {
        currentIndex = 0;
    }

    // 현재 섹션의 start, end time을 가져옴
    float endTime;
    animMontage->GetSectionStartAndEndTime(currentIndex, outWarpInfo.WarpConfig.WarpStartTime, endTime);
    outWarpInfo.WarpConfig.WarpEndTime = outWarpInfo.WarpConfig.WarpStartTime + ActionConfig.WarpInfo.WarpEndTime;

    if (ActionConfig.WarpInfo.TargetType == EWarpTargetType::ETargetTransform) 
    {
        const FTransform endTransform = GetWarpTransform();
        FVector localScale;
        UKismetMathLibrary::BreakTransform(endTransform, outWarpInfo.WarpLocation, outWarpInfo.WarpRotation, localScale);
    }
    else if (ActionConfig.WarpInfo.TargetType == EWarpTargetType::ETargetComponent) 
    {
        outWarpInfo.TargetComponent = GetWarpTargetComponent();
    }
}

FTransform UHyActionBase::GetWarpTransform_Implementation()
{
    ensure(false);
    return FTransform();
}

USceneComponent* UHyActionBase::GetWarpTargetComponent_Implementation()
{
    ensure(false);
    return nullptr;
}

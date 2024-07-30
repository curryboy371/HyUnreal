// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HyActionSetComponent.h"
#include "HyTypes.h"
#include "Action/HyActionComboBase.h"
#include "Character/HyPlayerCharacter.h"
#include "Animation/HyAnimInstance.h"
#include "HyGameplayTags.h"


// Sets default values for this component's properties
UHyActionSetComponent::UHyActionSetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    ActionsDataSet = UHyActionsDataAsset::StaticClass();

    ResetActionState();
	// ...
}


// Called when the game starts
void UHyActionSetComponent::BeginPlay()
{
	Super::BeginPlay();



    MovesetsActionsInst.Empty();
    for (const auto& actionssetclass : MovesetActions) 
    {
        if (actionssetclass.ActionsSet) 
        {
            UHyActionsDataAsset* moveset = NewObject<UHyActionsDataAsset>(this, actionssetclass.ActionsSet);
            MovesetsActionsInst.Add(actionssetclass.TagName, moveset);
        }
        else 
        {
            ERR_V("Invalid MovesetActions Class");
        }
    }

    CharacterOwner = Cast<AHyCharacter>(GetOwner());
    if (CharacterOwner) 
    {

        animInst = Cast<UHyAnimInstance>(CharacterOwner->GetMesh()->GetAnimInstance());
        if (animInst == nullptr)
        {
            ERR_V("Invalid animInst");
        }
    }
    else 
    {
        ERR_V("Invalid CharacterOwner");
    }

    if (ActionsDataSet)
    {
        FGameplayTag MovesetTag = FGameplayTag::EmptyTag;
        if (CharacterOwner)
        {
            MovesetTag = CharacterOwner->GetCurMovesetTag();
        }

        ActionsDataSetInst = NewObject<UHyActionsDataAsset>(this, ActionsDataSet);
        SetMovesetActions(MovesetTag); // character MoveActionSetTag로 초기 movesetTag를 세팅함
    }
    else
    {
        ERR_V("Invalid ActionsDataSet Class");
    }


    ResetActionState();

}


// Called every frame
void UHyActionSetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
    if (bIsPerformingAction && PerformingAction) 
    {
        PerformingAction->OnTick(DeltaTime);
    }
}

void UHyActionSetComponent::PlayMontage(const FHyMontageInfo& montageInfo, float StartFrame)
{
	MontageInfo = montageInfo;

    if (MontageInfo.MontageAction && CharacterOwner) 
    {
        CharacterOwner->PlayAnimMontage_Custom(MontageInfo.MontageAction,  MontageInfo.ReproductionSpeed, MontageInfo.MontageBlend, MontageInfo.StartSectionName, StartFrame);
    }
}

void UHyActionSetComponent::LaunchAction(const FGameplayTag& ActionState, const EActionPriority priority, const FString contextString)
{
    FHyActionState action;
    if (GetActionByTag(ActionState, action) && action.Action) 
    {
        if (PerformingAction) 
        {
            action.Action->OnActionTransition(PerformingAction);
            TerminateCurrentAction();
        }
        OnActionStarted.Broadcast(ActionState);

        PerformingAction = action.Action;
        CurrentActionTag = ActionState;
        bIsPerformingAction = true;
        PerformingAction->SetTerminated(false);

        if (animInst)
        {
            //animInst->SetActionPlaying(true);
        }

        PerformingAction->Internal_OnActivated(this, action.MontageAction, contextString);
        //ActionStart(ActionState, contextString);
        CurrentString = contextString;
        CurrentPriority = (int32)priority;

        if (PerformingAction && PerformingAction->GetActionConfig().bPlayEffectOnActionStart)
        {
            PerformingAction->PlayEffects();
        }
    }

}

void UHyActionSetComponent::FreeAction()
{
    if (StoredAction == FGameplayTag::EmptyTag)
    {
        SetDefaultStoredActionTag();
    }

    CurrentString.Empty();
    CurrentPriority = EmptyPriority;
    TriggerAction(StoredAction, (EActionPriority)StoredPriority, false, StoredString);
    StoreAction(FGameplayTag::EmptyTag);
}

//void UHyActionSetComponent::LaunchStoreAction(float InBlendOut)
//{
    // 사용안함
    //UHyActionComboBase* TestComboBase = Cast<UHyActionComboBase>(GetCurrentAction(StoredAction));
    //if(TestComboBase)
    //{
    //    int32 ComboIndex = TestComboBase->GetComboCounter();
    //    UE_LOG(LogTemp, Error, TEXT("ComboIndex : (%d)"),ComboIndex);
    //}
    //
    //if (StoredAction != FGameplayTag())
    //{
    //    CurrentPriority = -1;
    //    TriggerAction(StoredAction, (EActionPriority)StoredPriority, true, StoredString);
    //    StoreAction(FGameplayTag::EmptyTag);
    //}
    //else
    //{
    //    if(CharacterOwner)
    //    {
    //        if (CharacterOwner->GetIsInputMoving())
    //        {
    //            CharacterOwner->ActionStop(InBlendOut);
    //        }
    //
    //        CharacterOwner->ActionAllStepEnd(StoredAction);
    //    }
    //}
    
//}

void UHyActionSetComponent::SetCurrentAction(const FGameplayTag& ActionState)
{
    CurrentActionTag = ActionState;
}

void UHyActionSetComponent::StoreAction(FGameplayTag ActionState, const FString& contextString, const int32 InStorePriority)
{
    if (CharacterOwner->GetCharacterTag() == FGameplayTag::EmptyTag)
    {
        LOG_V("StoreAction %s To %s Contest %s", *StoredAction.ToString(), *ActionState.ToString(), *contextString);
    }

    StoredAction = ActionState;
    StoredString = contextString;
    StoredPriority = InStorePriority;


}

void UHyActionSetComponent::ActionStart(const FGameplayTag& ActionState, const FString& contextString)
{
    OnActionStarted.Broadcast(ActionState);
    FHyActionState action;

    if (GetActionByTag(ActionState, action) && action.Action)
    {
        PerformingAction = action.Action;
        action.Action->SetCharacterOwner(CharacterOwner);
        action.Action->OnActionStarted(contextString);
    }
}

void UHyActionSetComponent::ActionEnd(const FGameplayTag& ActionState)
{
    FHyActionState action;
    if (GetActionByTag(ActionState, action) && action.Action) 
    {
        action.Action->OnActionEnded();
    }


}

void UHyActionSetComponent::ActionStopImmeditaley(float InBlendOutTime/*  = 0.0f*/)
{
    if (StoredAction == FGameplayTag::EmptyTag)
    {
        SetDefaultStoredActionTag();
    }

    FHyActionState action;
    if (GetActionByTag(CurrentActionTag, action)) 
    {
        if (animInst)
        {
            animInst->Montage_Stop(InBlendOutTime, action.MontageAction);
        }
        else
        {
            ERR_V("animinst is null");
        }
    }
    CurrentPriority = EmptyPriority;
    CurrentString.Empty();

    InternalExitAction();
}

void UHyActionSetComponent::PauseAction(bool bSetPause)
{
    if (CharacterOwner && CharacterOwner->GetMesh())
    {
        CharacterOwner->GetMesh()->bPauseAnims = bSetPause;
    }
}

void UHyActionSetComponent::ClearPerformingActionState()
{
    if (PerformingAction)
    {
        PerformingAction->ClearActionState();
    }
}

void UHyActionSetComponent::SetPerformingActionPriority(EActionPriority Priority)
{
    CurrentPriority = (int32)Priority;
}

bool UHyActionSetComponent::IsActionStopCondition()
{
    // 현재 진행중인 Action을 조건에 따라 Stop or Continue
    if (PerformingAction)
    {
        return PerformingAction->IsStopConditional();
    }

    return false;
}

TObjectPtr<UHyActionBase> UHyActionSetComponent::GetCurrentAction(const FGameplayTag& ActionState)
{
    FHyActionState action;
    if (GetActionByTag(ActionState, action) && action.Action)
    {
        return action.Action;
    }
    return nullptr;
}

TObjectPtr<UAnimMontage> UHyActionSetComponent::GetCurrentMontage(const FGameplayTag& ActionState)
{
    FHyActionState action;
    if (GetActionByTag(CurrentActionTag, action)) 
    {
        return action.MontageAction;
    }

    return nullptr;
}

void UHyActionSetComponent::TriggerAction(FGameplayTag ActionState, EActionPriority Priority/* = EActionPriority::ELow*/, bool bCanBeStored, const FString& contextString)
{
    // ActionState 태그로 Action을 트리거하려고 시도하는 함수
    // Priority를 비교하여 Action이 실행될지, 무시될지, 
    // bCanBeStored가 true이고 진행중인 action이 있다면 다음 Action을 위해 저장될지 ( Priority도 비교)
    // contextString은 `OnActionStarted에서 받아 Flag 처럼 사용함

    if (!CharacterOwner) 
    {
        return;
    }

    if (ActionState == FGameplayTag::EmptyTag)
    {
        ERR_V("ActionState is EmptyTag");
        return;
    }

    OnActionTriggered.Broadcast(ActionState, Priority);

    FHyActionState action;
    if (GetActionByTag(ActionState, action) && action.Action && CanExecuteAction(ActionState)) 
    {
        if ((((int32)Priority > CurrentPriority)) || Priority == EActionPriority::EHighest) 
        {
            LaunchAction(ActionState, Priority, contextString);
        }
        else if (CurrentActionTag != FGameplayTag::EmptyTag && bCanBeStored) {
            StoreAction(ActionState, contextString, (int32)Priority);
        }
    }
    else 
    {
        WAR_V("Invalid Action");
    }
}

void UHyActionSetComponent::SetStoredActionTag(FGameplayTag ActionState, EActionPriority Priority/* = EActionPriority::ELow*/, bool bForce/* = false*/, const FString contextString/* = ""*/)
{
    if (bForce || StoredAction == FGameplayTag::EmptyTag || (int32)Priority > StoredPriority)
    {
        if (CharacterOwner->GetCharacterTag() == FGameplayTag::EmptyTag)
        {
            //LOG_V("SetStored %s To %s", *StoredAction.ToString(), *ActionState.ToString());
        }

        StoreAction(ActionState, contextString, (int32)Priority);

    }
    else
    {
        if (CharacterOwner->GetCharacterTag() == FGameplayTag::EmptyTag)
        {
            //LOG_V("Cant SetStored %s  Keep %s", *ActionState.ToString(), *StoredAction.ToString());
        }
    }
}

void UHyActionSetComponent::SetDefaultStoredActionTag(const bool bForce)
{
    FGameplayTag DefaultTag = FHyTags::Get().GetDefaultAction(GetPerformingActionTag());
    SetStoredActionTag(DefaultTag, EActionPriority::ENone, bForce);
}

void UHyActionSetComponent::SetTagActionRate(const FGameplayTag& ActionState, float Rate)
{
    FHyActionState action;
    if (GetActionByTag(ActionState, action) && action.Action)
    {
        action.Action->SetAnimRate(Rate);
    }
}

bool UHyActionSetComponent::CanExecuteAction(FGameplayTag ActionTag) const
{
    FHyActionState action;
    if (GetActionByTag(ActionTag, action) && action.Action)
    {
        return true;
    }
    else 
    {
        WAR_V("Actions Conditions are not verified")
    }
    return false;
}

void UHyActionSetComponent::InternalExitAction()
{
    if (bIsPerformingAction && PerformingAction) 
    {
        // 현재 액션 종료
        TerminateCurrentAction();

        FGameplayTag EmptyActionTag = FGameplayTag::EmptyTag;
        if (StoredAction != EmptyActionTag)
        {
            // NextAction
            TriggerAction(StoredAction, (EActionPriority)StoredPriority, false, StoredString);
            StoreAction(EmptyActionTag);
        }
        else 
        {
            // Not NextAction 
            SetCurrentAction(EmptyActionTag);
            ActionStart(EmptyActionTag, "");
            PerformingAction = nullptr;
        }

    }
}

void UHyActionSetComponent::TerminateCurrentAction()
{
    // 현재 진행중인 Action을 종료함
    if (bIsPerformingAction && PerformingAction && !PerformingAction->GetTerminated()) 
    {
        if (animInst)
        {
            //animInst->SetActionPlaying(false);
        }

        PerformingAction->Internal_OnDeactivated();
        PerformingAction->SetTerminated(true);
        PerformingAction = nullptr;
        OnActionFinished.Broadcast(CurrentActionTag);
        //ActionEnd(CurrentActionTag);
        CurrentActionTag = FGameplayTag::EmptyTag;
        CurrentPriority = EmptyPriority;
        CurrentString.Empty();

    }
    bIsPerformingAction = false;
}

void UHyActionSetComponent::SetMovesetActions(const FGameplayTag& movesetActionsTag)
{
    if (movesetActionsTag == FGameplayTag::EmptyTag)
    {
        ERR_V("MovesetTag is Empty");
        return;
    }

    LOG_V("MovesetTag Change %s to %s", *currentMovesetActionsTag.ToString(), *movesetActionsTag.ToString());
    currentMovesetActionsTag = movesetActionsTag;
}

bool UHyActionSetComponent::GetActionByTag(const FGameplayTag& Action, FHyActionState& outAction) const
{
    // Action이 유효한지 Check한 후 outAction에 반환
    if (ActionsDataSetInst)
    {
        if (GetMovesetActionByTag(Action, currentMovesetActionsTag, outAction)) 
        {
            // 1. 현재 MovesetTag와 일치하는 Moveset Action이 있는지 체크
            return true;
        }
        else if (GetCommonActionByTag(Action, outAction)) 
        {
            // 2. 1이 없다면 공용 Action이 있는지 체크
            return true;
        }
    }
    else 
    {
        return false;
    }
    return false;
}

bool UHyActionSetComponent::GetMovesetActionByTag(const FGameplayTag& action, const FGameplayTag& Moveset, FHyActionState& outAction) const
{
    // Moveset에서 tag로 action을 찾아 반환
    if (MovesetsActionsInst.Contains(Moveset)) 
    {
        UHyActionsDataAsset* actionSet = MovesetsActionsInst.FindChecked(Moveset);
        if (actionSet) {
            return actionSet->GetActionByTag(action, outAction);
        }
    }
    return false;
}

bool UHyActionSetComponent::GetCommonActionByTag(const FGameplayTag& action, FHyActionState& outAction) const
{
    if (ActionsDataSetInst)
    {
        return ActionsDataSetInst->GetActionByTag(action, outAction);
    }
    return false;
}

const FGameplayTag UHyActionSetComponent::GetPerformingActionTag() const
{
    FGameplayTag PerformingTag = FGameplayTag::EmptyTag;

    if (bIsPerformingAction && PerformingAction)
    {
        PerformingTag =  PerformingAction->GetActionTag();

    }

    return PerformingTag;
}

const FGameplayTag UHyActionSetComponent::GetStoredActionTag() const
{
    return StoredAction;
}

const bool UHyActionSetComponent::IsDefaultStoredAction() const
{
    FGameplayTag DefaultTag = FHyTags::Get().GetDefaultAction(GetPerformingActionTag());
    if (StoredAction == DefaultTag)
    {
        return true;
    }
    return false;
}

const bool UHyActionSetComponent::IsEmptyStoredAction() const
{
    if (StoredAction == FGameplayTag::EmptyTag)
    {
        return true;
    }

    return false;
}

const bool UHyActionSetComponent::IsLastMonstageSection() const
{
    // 현재 재생중인 몽타주가 마지막 섹션인지?
    if (bIsPerformingAction && PerformingAction)
    {
        if (PerformingAction->GetCurMontageSectionIdx() + 1 == PerformingAction->GetCurMontageSectionLength())
        {
            return true;
        }
    }
    return false;
}

void UHyActionSetComponent::ResetActionState()
{
    // reset value
    CurrentActionTag = FGameplayTag::EmptyTag;
    CurrentPriority = EmptyPriority;
    CurrentString.Empty();

    StoredAction = FGameplayTag::EmptyTag;
    StoredPriority = EmptyPriority;
    StoredString.Empty();
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AI_NormalAttack.h"

#include "HyTypes.h"
#include "Action/HyActionTypes.h"
#include "Character/HyCharacter.h"
#include "AI/HyAIController.h"

void UHyAction_AI_NormalAttack::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);

	if (HyAIController)
	{
		HyAIController->SetBBValue<bool>(FName("bCanAttack"), false);
	}

	//if (CharacterOwner)
	//{
	//	CharacterOwner->SetIsAttacking(true);
	//}

}

void UHyAction_AI_NormalAttack::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
	//if (CharacterOwner)
	//{
	//	CharacterOwner->SetIsAttacking(false);
	//}

}

void UHyAction_AI_NormalAttack::OnActionTransition_Implementation(UHyActionBase* previousState)
{
	Super::OnActionTransition_Implementation(previousState);
	// Action이 전환되었을때 실행됨.

}

bool UHyAction_AI_NormalAttack::IsStopConditional_Implementation()
{
    Super::IsStopConditional_Implementation();

    //UHyActionComboBase* TestComboBase = Cast<UHyActionComboBase>(GetCurrentAction(StoredAction));
    //if (TestComboBase)
    //{
    //    int32 ComboIndex = TestComboBase->GetComboCounter();
    //    UE_LOG(LogTemp, Error, TEXT("ComboIndex : (%d)"), ComboIndex);
    //}
    // 위 로그 아래로 변경
    //int32 ComboIndex = GetComboCounter();
    ///UE_LOG(LogTemp, Error, TEXT("ComboIndex : (%d)"), ComboIndex);

    if (CharacterOwner)
    {
        // 어차피 Stored되어있을테니깐
        // 입력이 없으면 Idle로 들어와서 공격이 스스로 끝날때까지 기다린 후 Idle 실행

        // 입력이 있으면 Stored에 Move 액션들어오고 실행되도록 Free
        // 공격이 입력되면 콤보 공격을 실행하도록 Free
        if (!CharacterOwner->IsEmptyStoredAction())
        {
            CharacterOwner->HandleActionExit(EActionHandleExitType::EActionExit_Stop);
        
            // 직접 Free를 해주려고 return을 일부러 false 반환
            return false;
        }
    }
    return false;
}

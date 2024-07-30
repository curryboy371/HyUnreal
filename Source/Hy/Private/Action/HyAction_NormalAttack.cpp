// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_NormalAttack.h"

#include "Game/HyGameModeBase.h"


#include "HyTypes.h"
#include "Character/HyCharacter.h"
#include "Action/HyActionTypes.h"
#include "HyGameplayTags.h"
#include "Kismet/KismetMathLibrary.h"

#include "Animation/HyAnimInstance.h"

void UHyAction_NormalAttack::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);

	if (CharacterOwner)
	{
        SetOwnerCharacterRotation();

        //CharacterOwner->SetCanAttack(false);

        //CharacterOwner->SetUseSeparateBrakingFriction(false);

        // Dash 시도 후 Attack로 전환되었는데 Dash를 계속 누르고 있던 경우
        // TODO Idle 코드와 합쳐야함
        //if (CharacterOwner->IsDashPressed() && CharacterOwner->GetMoveMode() == EMoveMode::ESprint)
        //{
        //    UHyAnimInstance* AnimInst = Cast<UHyAnimInstance>(CharacterOwner->GetMesh()->GetAnimInstance());
        //    if (AnimInst == nullptr)
        //    {
        //        ERR_V("anim instance is null");
        //        return;
        //    };
        //
        //    LOG_V("Run Change On Idle Tick");
        //
        //    AnimInst->SetAnimMoveMode(true);
        //    CharacterOwner->SwichMovementMode(EMoveMode::ERun);
        //}

	}

}

void UHyAction_NormalAttack::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();

    // 콤보 실패시 초기화
    if (!bSuccesfulCombo)
    {
        if (CharacterOwner)
        {
            //CharacterOwner->SetIsAttacking(false);
            //CharacterOwner->SetUseSeparateBrakingFriction(true);
        }
    }

}

void UHyAction_NormalAttack::OnActionTransition_Implementation(UHyActionBase* previousState)
{
	Super::OnActionTransition_Implementation(previousState);

	// Action이 전환되었을때 실행됨.

}

bool UHyAction_NormalAttack::IsStopConditional_Implementation()
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
    //UE_LOG(LogTemp, Error, TEXT("ComboIndex : (%d)"), ComboIndex);

    if (CharacterOwner)
    {
        // 언제든지 다음 액션이 진행되도록 프로퍼티 낮춤
        CharacterOwner->SetPerformingActionPriority(EActionPriority::ENone);

        //// 입력이 없으면 Idle로 들어와서 공격이 스스로 끝날때까지 기다린 후 Idle 실행
        //
        //// 공격이 입력되면 콤보 공격을 실행하도록 Free
        //// 다음 액션이 Attacking이라면 콤보공격을 실행하도록 Free
        if (FHyTags::Get().ActionAttack.MatchesTag(CharacterOwner->GetStoredActionTag()))
        {
            CharacterOwner->HandleActionExit(EActionHandleExitType::EActionExit_Free);
        }
        else if(FHyTags::Get().IsMoveAction(CharacterOwner->GetStoredActionTag()))
        {
            // MoveAction이 예약되어 있다면 AnimState에서 즉시 실행하도록 STop
            CharacterOwner->HandleActionExit(EActionHandleExitType::EActionExit_Stop);
        }
        
        if (!CharacterOwner->IsEmptyStoredAction())
        {
            //CharacterOwner->ActionAllStepEnd(CharacterOwner->GetStoredActionTag());
            // 직접 Free를 해주려고 return을 일부러 false 반환
            return false;
        }

    }
	return false;
}

void UHyAction_NormalAttack::SetOwnerCharacterRotation()
{
    // OnwerCharacter를 회전시키는 함수
    // 공격 가능한 타겟이 있다면 그 타겟을 바라보게 회전
    // 위 상황이 아니라면 Input 방향에 맞게 회전

    if (!CharacterOwner)
    {
        ERR_V("CharacterOwner is invalid");
        return;
    }

    AHyGameModeBase* GameMode = Cast<AHyGameModeBase>(UGameplayStatics::GetGameMode(CharacterOwner->GetWorld()));
    if (GameMode == nullptr)
    {
        ERR_V("GameMode is invalid");
        return;
    }

    FRotator InputRotation = CharacterOwner->GetActorRotation();
   // bool bInputRotation = CharacterOwner->GetIsInputMoving();

   //if (CharacterOwner->IsTargetAvailable())
   //{
   //    // TODO 타겟 공격 범위 체크 수정 필요함
   //    // 타겟이 있다면 공격 범위를 체크하여 타겟 방향으로 회전
   //    FVector TargetLocation;
   //    float TargetCapsuleRadius;
   //    if (GameMode->GetCharacterLocation(CharacterOwner->GetTargetGuidRef(), TargetLocation) &&
   //        GameMode->GetCharacterCapsuleRadius(CharacterOwner->GetTargetGuidRef(), TargetCapsuleRadius) &&
   //        CharacterOwner->IsInAttackRange(TargetLocation, TargetCapsuleRadius))
   //    {
   //        FVector LookVector = TargetLocation - CharacterOwner->GetActorLocation();
   //        InputRotation = FRotationMatrix::MakeFromX(LookVector).Rotator();
   //        InputRotation.Pitch = 0;
   //        CharacterOwner->SetActorRotation(InputRotation);
   //        bInputRotation = false;
   //    }
   //}
   //
   //// 회전 가능한 타겟이 없고 키보드를 입력 중이라면
   //// 입력하는 방향으로 회전시킨다
   //if (bInputRotation)
   //{
   //    FVector LookVector = CharacterOwner->GetInputDirection();
   //    if (!LookVector.IsNearlyZero())
   //    {
   //        InputRotation = FRotationMatrix::MakeFromX(LookVector).Rotator();
   //        InputRotation.Pitch = 0;
   //        CharacterOwner->SetActorRotation(InputRotation);
   //    }
   //}


}

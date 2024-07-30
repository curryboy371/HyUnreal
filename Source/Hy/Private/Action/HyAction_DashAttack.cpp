// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_DashAttack.h"
#include "Character/HyCharacter.h"
#include "HyGameplayTags.h"
#include "Game/HyGameModeBase.h"
#include "Kismet/KismetMathLibrary.h"

//#include "Character/NPCharactorStatComponent.h"


void UHyAction_DashAttack::OnActionStarted_Implementation(const FString& contextString)
{
	ElapsedTime = 0.0f;
	DeltaTimeInterval = 0.06;

	Super::OnActionStarted_Implementation(contextString);
	if (!CharacterOwner)
	{
		ERR_V("CharacterOwner is null");
		return;
	}

	//TObjectPtr<UNPCharactorStatComponent> CharacterStatCom = (CharacterOwner->GetStatComponent());
	//
	//if (!CharacterStatCom)
	//{
	//	ERR_V("CharacterStatCom is null");
	//	return;
	//}
	//
	//ANPGameMode* GameMode = Cast<ANPGameMode>(UGameplayStatics::GetGameMode(CharacterOwner->GetWorld()));
	//if (GameMode == nullptr)
	//{
	//	ERR_V("GameMode is invalid");
	//	return;
	//}
	//
	//CharacterOwner->SetUseSeparateBrakingFriction(false);
	//
	//if (CharacterOwner->IsTargetAvailable())
	//{
	//	// 첫타는 워핑
	//	FVector Location;
	//
	//	if (GameMode->GetCharacterCombatLocation(CharacterOwner->GetActorLocation(), CharacterStatCom->GetTotalStat().AutoAttackRange, CharacterOwner->GetTargetGuidRef(), Location))
	//	{
	//		CharacterOwner->SetDashWarpingTarget(Location);
	//		WarpLocation = Location;
	//	}
	//}

}

void UHyAction_DashAttack::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
	ElapsedTime += DeltaTime;

	//if (ElapsedTime > DeltaTimeInterval)
	//{
	//	ElapsedTime = 0.0f;
	//
	//	if (CharacterOwner->IsTargetAvailable())
	//	{
	//		TObjectPtr<UNPCharactorStatComponent> CharacterStatCom = (CharacterOwner->GetStatComponent());
	//
	//		if (!CharacterStatCom)
	//		{
	//			ERR_V("CharacterStatCom is null");
	//			return;
	//		}
	//
	//		ANPGameMode* GameMode = Cast<ANPGameMode>(UGameplayStatics::GetGameMode(CharacterOwner->GetWorld()));
	//		if (GameMode == nullptr)
	//		{
	//			ERR_V("GameMode is invalid");
	//			return;
	//		}
	//
	//		// 워핑 추적
	//
	//
	//
	//		FVector Location;
	//
	//
	//		if (GameMode->GetCharacterCombatLocation(CharacterOwner->GetActorLocation(), CharacterStatCom->GetTotalStat().AutoAttackRange, CharacterOwner->GetTargetGuidRef(), Location))
	//		{
	//			FVector Distance = WarpLocation - Location;
	//			if (Distance.Length() > 1.f)
	//			{
	//				CharacterOwner->SetDashWarpingTarget(Location);
	//				WarpLocation = Location;
	//			}
	//
	//
	//		}
	//	}
	//}
}

void UHyAction_DashAttack::OnActionEnded_Implementation()
{
	//Super::OnActionEnded_Implementation();
	//if (CharacterOwner)
	//{
	//	CharacterOwner->ReleaseWarpingTarget();
	//	CharacterOwner->SetUseSeparateBrakingFriction(true);
	//
	//}
}

bool UHyAction_DashAttack::IsStopConditional_Implementation()
{
	Super::IsStopConditional_Implementation();

	//if (CharacterOwner)
	//{
	//	// 언제든지 다음 액션이 진행되도록 프로퍼티 낮춤
	//	CharacterOwner->SetPerformingActionPriority(EActionPriority::ENone);
	//
	//	//// 입력이 없으면 Idle로 들어와서 공격이 스스로 끝날때까지 기다린 후 Idle 실행
	//	//
	//	//// 공격이 입력되면 콤보 공격을 실행하도록 Free
	//	//// 다음 액션이 Attacking이라면 콤보공격을 실행하도록 Free
	//	if (FHyTags::Get().ActionAttack.MatchesTag(CharacterOwner->GetStoredActionTag()))
	//	{
	//		CharacterOwner->HandleActionExit(EActionHandleExitType::EActionExit_Free);
	//	}
	//	else if (FHyTags::Get().IsMoveAction(CharacterOwner->GetStoredActionTag()))
	//	{
	//		// MoveAction이 예약되어 있다면 AnimState에서 즉시 실행하도록 STop
	//		CharacterOwner->HandleActionExit(EActionHandleExitType::EActionExit_Stop);
	//	}
	//
	//	if (!CharacterOwner->IsEmptyStoredAction())
	//	{
	//		CharacterOwner->ActionAllStepEnd(CharacterOwner->GetStoredActionTag());
	//		// 직접 Free를 해주려고 return을 일부러 false 반환
	//		return false;
	//	}
	//
	//}
	return false;
}

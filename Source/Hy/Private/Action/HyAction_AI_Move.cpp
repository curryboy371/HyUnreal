// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AI_Move.h"
#include "Character/HyCharacter.h"
#include "AI/HyAIController.h"
#include "HyTypes.h"
#include "Game/HyDeveloperSettings.h"
#include "HyGameplayTags.h"


void UHyAction_AI_Move::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);
	LastAIMoveType = EAIMoveType::EAIMove_None;


	IsWalkMode = FHyTags::Get().IsMoveWalk(ActionTag);

	if (HyAIController)
	{
		HyAIController->SetBBValue<bool>(FName("bMoveFinish"), false);
	}

	ElapsedTime = 0.f;
	RetryMoveCount = 0;
	ToleranceDistance = 0.0f;

	bHasDestination = FindMoveDestination();

	
}

void UHyAction_AI_Move::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

	ElapsedTime += DeltaTime;

	//if (!NPAIInterface || !HyAIController || !CharacterOwner)
	//{
	//	ERR_V("Invalid Ptrs");
	//	return;
	//}

	if (bHasDestination && IsAtDestination())
	{
		// 목적지에 도달
		ArrivalAtDestination();
	}
	else
	{
		// 아직 목적지에 도달하지 못한 경우
		if (DeltaTimeInterval < ElapsedTime)
		{
			ElapsedTime = 0;
			MoveRetry();
		}
	}

	if (const UHyDeveloperSettings* DevSetting = UHyDeveloperSettings::GetDeveloperSetting())
	{
		if (DevSetting->IsDebugDraw())
		{
			DebugDrawMoveArrow();
		}
	}
}

void UHyAction_AI_Move::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();

}

void UHyAction_AI_Move::ArrivalAtDestination()
{
	//if (!NPAIInterface || !HyAIController || !CharacterOwner)
	//{
	//	ERR_V("Invalid Ptrs");
	//	return;
	//}

	// 목적지 도달
	//NPAIInterface->ResetDestLocation(CharacterOwner->GetActorLocation());

	if (IsWalkMode)
	{
		HyAIController->SetBBValue<bool>(FName("bMoveFinish"), true);
	}
	else
	{
		// 현재 없음
		// HyAIController->SetBBValue<bool>(FName("bMoveFinish"), true);
	}
}

void UHyAction_AI_Move::MoveRetry()
{
	//if (!NPAIInterface || !HyAIController || !CharacterOwner)
	//{
	//	ERR_V("Invalid Ptrs");
	//	return;
	//}


	// 길찾기 재시도
	if (ShouldRetryMove())
	{
		RetryMoveDest();
	}
}

const bool UHyAction_AI_Move::ShouldRetryMove()
{
	//if (!NPAIInterface || !HyAIController || !CharacterOwner)
	//{
	//	ERR_V("Invalid Ptrs");
	//	return false;
	//}

	//if (NPAIInterface->IsTargetMoving(LastAIMoveType))
	//{
	//	return true; // Follower인 경우 타겟이 계속 이동중인 경우
	//}

	if (CharacterOwner->GetVelocity().Length() < 5.0f)
	{
		return true; // AI 캐릭터가 너무 느린 상태인 경우
	}

	return false;
}

bool UHyAction_AI_Move::FindMoveDestination()
{
	bool bFindResult = false;

	//if (!NPAIInterface || !HyAIController || !CharacterOwner)
	//{
	//	ERR_V("Invalid Ptrs");
	//	return bFindResult;
	//}

	// 이동할 위치를 찾음
	//NPAIInterface->ResetDestLocation(CharacterOwner->GetActorLocation());
		
	if (IsWalkMode)
	{
		ToleranceDistance = 50.0f;
		//CharacterOwner->SwichMovementMode(EMoveMode::ERun); // Temp

		//LastAIMoveType = NPAIInterface->FindAIMoveDestLocation();

		if (LastAIMoveType != EAIMoveType::EAIMove_None)
		{
			//HyAIController->MoveToLocation(NPAIInterface->GetDestLocation());
			bFindResult = true;
		}
	}
	else
	{
		// 현재 없는 상태
	}

	return bFindResult;
}

bool UHyAction_AI_Move::IsAtDestination()
{
	// 목적지에 도달했는지 체크
	//if (CharacterOwner && NPAIInterface)
	//{
	//	if (NPAIInterface->IsNearDestLocation(CharacterOwner, ToleranceDistance))
	//	{
	//		return true;
	//	}
	//}

	return false;
}

void UHyAction_AI_Move::RetryMoveDest()
{
	//if (!NPAIInterface || !HyAIController || !CharacterOwner)
	//{
	//	ERR_V("Invalid Ptrs");
	//	return;
	//}

	if (RetryMoveCount < 2)
	{
		// 목적지에 도달하지 못했으면 재시도
		//HyAIController->MoveToLocation(NPAIInterface->GetDestLocation());
		++RetryMoveCount;
		LOG_V("Retry MovetoLocation Attempt  %d", RetryMoveCount);
	}
	else
	{
		// Retry 초과시 목적지를 다시 설정
		if (!FindMoveDestination())
		{
			// 목적지 찾기에 실패하면 Move Action을 종료함
			HyAIController->SetBBValue<bool>(FName("bMoveFinish"), true);
		}

		RetryMoveCount = 0;
	}
}


void UHyAction_AI_Move::DebugDrawMoveArrow()
{
	//if (CharacterOwner && NPAIInterface)
	//{
	//	FVector StartLocation = CharacterOwner->GetActorLocation();
	//	FVector EndLocation = NPAIInterface->GetDestLocation();
	//	EndLocation.Z = StartLocation.Z;
	//
	//	UHyFunctionLib::DrawArrow(GetWorld(), StartLocation, EndLocation, 30, FLinearColor::Black);
	//}

}

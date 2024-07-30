// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_MoveBase.h"

#include "Action/HyAction_Dash.h"

#include "Character/HyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/Vector.h"

#include "Hy.h"

void UHyAction_MoveBase::OnActionStarted_Implementation(const FString& contextString)
{
	// dash direction 설정
	bStopMove = false;
	bStopAction = false;
	bIsAtDestination = false;

	//CharacterOwner->SetDashDestLocation(true);
	StartLocation = CharacterOwner->GetActorLocation();
	//DestLocation = CharacterOwner->GetDashDestLocation();
	DashDirection = (DestLocation - StartLocation).GetSafeNormal2D();
}

void UHyAction_MoveBase::OnTick_Implementation(float DeltaTime)
{
	if (!bStopMove)
	{
		float Progress = 0.0f;
		if (GetMontageProgress(Progress))
		{
			Progress = FMath::Clamp(Progress, 0.0f, 1.0f);
			//CharacterOwner->AddCharacterMovementInput(DashDirection, 1 - Progress);
		}
	}
}

void UHyAction_MoveBase::OnActionEnded_Implementation()
{
	if (CharacterOwner)
	{

		//CharacterOwner->SetDashDestLocation(false);
		//CharacterOwner->SwichMovementMode(EMoveMode::ERun);
		//
		//// 동일한 방향으로 이동하여 액션이 중간에 끊어진 경우
		//if (bStopAction)
		//{
		//	CharacterOwner->SetMaxAccelTempBoost();
		//}
	}
}

bool UHyAction_MoveBase::IsStopConditional_Implementation()
{
	bool KeepVelocity = false;
	bStopMove = true;
	if (CharacterOwner)
	{
		//if (CharacterOwner->GetIsInputMoving())
		//{
		//	FVector InputDir = CharacterOwner->GetInputDirection().GetSafeNormal(); // 단위 벡터로 정규화
		//	float DotProduct2D = InputDir.X * DashDirection.X + InputDir.Y * DashDirection.Y;
		//	float RadianAngle = FMath::Acos(DotProduct2D);
		//	float DegreeAngle = FMath::RadiansToDegrees(RadianAngle);
		//
		//	// 구르기 방향과 INPUT 방향 벡터의 사이각이KeekDashVelocityAngle보다 작으면
		//	// 현재 action 즉시 stop
		//	LOG_V("DegreeAngle %f", DegreeAngle);
		//
		//	if (DegreeAngle < KeekDashVelocityAngle)
		//	{
		//		KeepVelocity = true;
		//		bStopAction = true;
		//	}
		//}
	}
	return KeepVelocity;
}

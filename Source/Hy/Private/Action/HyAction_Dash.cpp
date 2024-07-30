// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Dash.h"

#include "Character/HyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/Vector.h"

#include "Hy.h"
//#include "Character/HyCharacterPlayer.h"
//#include "Character/NPTestPlayer.h"

#include "Game/HyDeveloperSettings.h"
#include "Animation/HyAnimInstance.h"

void UHyAction_Dash::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);
	//CharacterOwner->SetDashWarpingTarget();
	if (!CharacterOwner)
	{
		ERR_V("CharacterOwner is null");
		return;
	}

	//CharacterOwner->SetDashing(true);
	//CharacterOwner->SwichMovementMode(EMoveMode::EDash);
	bMoveStop = false;

	// if (const UNPDeveloperSettings* DevSetting = UNPDeveloperSettings::GetDeveloperSetting())
	// {
	// 	if (DevSetting->IsEnableBlur())
	// 	{
	// 		// 모션블러 활성화
	// 		ANPPlayerBase* player = Cast<ANPPlayerBase>(CharacterOwner);
	// 		if (nullptr != player)
	// 		{
	// 			player->SetCameraMotionBlue(true);
	// 		}
	// 	}
	// }
}

void UHyAction_Dash::OnTick_Implementation(float DeltaTime)
{
	//Super::OnTick_Implementation(DeltaTime);
	if (!bMoveStop)
	{
		//CharacterOwner->AddCharacterMovementInput(DashDirection);
	}
}

void UHyAction_Dash::OnActionEnded_Implementation()
{
	//Super::OnActionEnded_Implementation();

	if (!CharacterOwner)
	{
		return;
	}

	UHyAnimInstance* AnimInst = Cast<UHyAnimInstance>(CharacterOwner->GetMesh()->GetAnimInstance());
	if (AnimInst == nullptr)
	{
		ERR_V("anim instance is null");
		return;
	};


	//CharacterOwner->SetDashDestLocation(false);
	////CharacterOwner->SetDashing(false);
	//
	//if (CharacterOwner->IsDashPressed() && CharacterOwner->GetIsInputMoving())
	//{
	//	AnimInst->SetAnimMoveMode(false);
	//	CharacterOwner->SwichMovementMode(EMoveMode::ESprint);
	//}
	//else
	//{
	//	AnimInst->SetAnimMoveMode(true);
	//	CharacterOwner->SwichMovementMode(EMoveMode::ERun);
	//}


	// if (const UNPDeveloperSettings* DevSetting = UNPDeveloperSettings::GetDeveloperSetting())
	// {
	// 	if (DevSetting->IsEnableBlur())
	// 	{
	// 		// 모션블러 비활성화
	// 		ANPPlayerBase* player = Cast<ANPPlayerBase>(CharacterOwner);
	// 		if (nullptr != player)
	// 		{
	// 			player->SetCameraMotionBlue(false);
	// 		}
	// 	}
	// }
}

bool UHyAction_Dash::IsStopConditional_Implementation()
{
	Super::IsStopConditional_Implementation();

	bool bSprintOn = false;
	if (CharacterOwner)
	{
		// 먼저 Run으로 교체
		bMoveStop = true;

	}
	return false;
}

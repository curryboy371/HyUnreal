// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Idle.h"

#include "Character/HyCharacter.h"
#include "Animation/HyAnimInstance.h"
#include "Hy.h"

void UHyAction_Idle::OnActionStarted_Implementation(const FString& contextString)
{
}

void UHyAction_Idle::OnTick_Implementation(float DeltaTime)
{

	if (CharacterOwner)
	{
		// Dash 시도 후 Idle로 전환되었는데 Dash를 계속 누르고 있던 경우
		//if (CharacterOwner->IsDashPressed() && CharacterOwner->GetMoveMode() == EMoveMode::ESprint)
		//{
		//	// CheckVelocity
		//	if (CharacterOwner->GetMoveModeMaxSpeed(EMoveMode::ERun) > CharacterOwner->GetCharacterCurrentSpeeed())
		//	{
		//		UHyAnimInstance* AnimInst = Cast<UHyAnimInstance>(CharacterOwner->GetMesh()->GetAnimInstance());
		//		if (AnimInst == nullptr)
		//		{
		//			ERR_V("anim instance is null");
		//			return;
		//		};
		//
		//		AnimInst->SetAnimMoveMode(true);
		//		CharacterOwner->SwichMovementMode(EMoveMode::ERun);
		//
		//		LOG_V("Run Change On Idle Tick");
		//	}
		//
		//}
	}
}

void UHyAction_Idle::OnActionEnded_Implementation()
{


}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AI_Dead.h"
#include "Character/HyCharacter.h"
#include "Animation/HyAnimInstance.h"
#include "Animation/AnimMontage.h"


void UHyAction_AI_Dead::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);

	// MontageInfo가 세팅되기 전이므로 animMontage으로 접근하여 몽타주 길이를 구함

	if (contextString == "Pause")
	{
		if (animMontage)
		{
			float MontageLength = animMontage->GetSectionLength(0);
			StartFrame = MontageLength - 0.1f;
		}
	}
}

void UHyAction_AI_Dead::OnActionSetupCompleted_Implementation(const FString& contextString)
{
	if (contextString == "Pause")
	{
		PauseDeadAnim();
	}
}

void UHyAction_AI_Dead::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

}

void UHyAction_AI_Dead::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();

	
}

void UHyAction_AI_Dead::PauseDeadAnim()
{
	if (CharacterOwner && CharacterOwner->GetMesh())
	{
		CharacterOwner->PauseAction(true);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AI_Damaged_Standing.h"
#include "Character/HyCharacter.h"
#include "HyGameplayTags.h"
#include "Action/HyActionTypes.h"

void UHyAction_AI_Damaged_Standing::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);

	if (CharacterOwner)
	{
		CharacterOwner->SetStoredAction(FHyTags::Get().GetDefaultAction(ActionTag), EActionPriority::ENone, true);
	}
}

void UHyAction_AI_Damaged_Standing::OnActionTransition_Implementation(UHyActionBase* previousState)
{
	Super::OnActionTransition_Implementation(previousState);

}

void UHyAction_AI_Damaged_Standing::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
	if (CharacterOwner)
	{
		//float Progress = 0.0f;
		//if (GetMontageProgress(Progress))
		//{
		//	if (Progress > 0.5f)
		//	{
		//		if (CharacterOwner->GetIsStand() == false)
		//		{
		//			CharacterOwner->SetStandType(true);
		//		}
		//	}
		//
		//}

	}

}

void UHyAction_AI_Damaged_Standing::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
	//CharacterOwner->SetStandType(true);


}



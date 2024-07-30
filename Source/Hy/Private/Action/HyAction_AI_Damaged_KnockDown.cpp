// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AI_Damaged_KnockDown.h"
#include "Character/HyCharacter.h"
#include "HyGameplayTags.h"
#include "Action/HyActionTypes.h"

void UHyAction_AI_Damaged_KnockDown::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);
	if (CharacterOwner)
	{
		//CharacterOwner->SetStandType(false);
		//CharacterOwner->SetDownRemainTime(5.0f);
		CharacterOwner->SetStoredAction(FHyTags::Get().ActionKeepDown, EActionPriority::EHighest);
	}
}

void UHyAction_AI_Damaged_KnockDown::OnActionTransition_Implementation(UHyActionBase* previousState)
{
	Super::OnActionTransition_Implementation(previousState);

}

void UHyAction_AI_Damaged_KnockDown::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}

void UHyAction_AI_Damaged_KnockDown::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

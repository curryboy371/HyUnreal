// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AI_Damaged_KeepDown.h"
#include "Character/HyCharacter.h"
#include "HyGameplayTags.h"

void UHyAction_AI_Damaged_KeepDown::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);
}
void UHyAction_AI_Damaged_KeepDown::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

	if (CharacterOwner)
	{
		//if (CharacterOwner->UpdateDownRemainTime(DeltaTime) == false)
		//{
		//
		//}
	}
}

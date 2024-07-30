// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AI_KeepDown.h"
#include "Character/HyCharacter.h"
#include "HyGameplayTags.h"

void UHyAction_AI_KeepDown::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);

}

void UHyAction_AI_KeepDown::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

	//if (CharacterOwner)
	//{
	//	if (CharacterOwner->UpdateDownRemainTime(DeltaTime) == false)
	//	{
	//		if (CharacterOwner->IsDead() == false)
	//		{
	//			CharacterOwner->TriggerAction(FHyTags::Get().ActionHitTransit.Stand, EActionPriority::EHighest);
	//		}
	//	}
	//}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_SkillBase.h"

#include "HyTypes.h"
#include "Character/HyCharacter.h"


void UHyAction_SkillBase::OnActionStarted_Implementation(const FString& contextString)
{
	ElapsedTime = 0.0f;

	Super::OnActionStarted_Implementation(contextString);
	//if (CharacterOwner)
	//{
	//	CharacterOwner->SetUseSeparateBrakingFriction(false);
	//}
}

void UHyAction_SkillBase::OnTick_Implementation(float DeltaTime)
{
	ElapsedTime += DeltaTime;

	if (DeltaTimeInterval > DeltaTimeInterval)
	{


	}
}

void UHyAction_SkillBase::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
	//if (CharacterOwner)
	//{
	//	CharacterOwner->SetUseSeparateBrakingFriction(true);
	//}
}

bool UHyAction_SkillBase::IsStopConditional_Implementation()
{
	return true;
}

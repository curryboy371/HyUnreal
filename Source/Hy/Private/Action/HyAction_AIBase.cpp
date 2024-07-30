// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AIBase.h"
#include "HyTypes.h"
//#include "Character/NPCharacterNPC.h"
#include "AI/HyAIController.h"

//#include "Interface/NPCharacterAIInterface.h"


#include "HyGameplayTags.h"
#include "Character/HyCharacter.h"

UHyAction_AIBase::UHyAction_AIBase()
{
	//NPAIInterface = nullptr;
	HyAIController = nullptr;
}

void UHyAction_AIBase::OnActionStarted_Implementation(const FString& contextString)
{
	if (CharacterOwner)
	{
		//NPAIInterface = Cast<INPCharacterAIInterface>(CharacterOwner);
		//if (NPAIInterface == nullptr)
		//{
		//	ERR_V("NPAIInterface Casting Error");
		//}

		//bIsFollowObject = NPAIInterface->IsFollowerObject();

		HyAIController = Cast<AHyAIController>(CharacterOwner->GetController());
		if (HyAIController == nullptr)
		{
			ERR_V("HyAIController Casting Error");
		}
	}
	else 
	{
		ERR_V("CharacterOwner Casting Error");
	}


	if (CharacterOwner)
	{
		if (CharacterOwner->GetCharacterTag() == FGameplayTag::EmptyTag)
		{
			WAR_V("OnActionStart %s", *ActionTag.ToString())
		}
	}

}

void UHyAction_AIBase::OnTick_Implementation(float DeltaTime)
{

}

void UHyAction_AIBase::OnActionEnded_Implementation()
{
	if (CharacterOwner)
	{
		if (CharacterOwner->GetCharacterTag() == FGameplayTag::EmptyTag)
		{
			WAR_V("OnActionEnd %s", *ActionTag.ToString())
		}
	}
}

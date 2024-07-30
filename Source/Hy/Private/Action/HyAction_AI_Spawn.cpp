// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AI_Spawn.h"
#include "Character/HyCharacter.h"
#include "AI/HyAIController.h"


void UHyAction_AI_Spawn::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);
	if (CharacterOwner && HyAIController)
	{
		//if (NPAIInterface)
		//{
		//	NPAIInterface->ResetDestLocation(CharacterOwner->GetActorLocation());
		//}
		//CharacterOwner->SetIdleState();
		//CharacterOwner->SetIsInit();
		HyAIController->SetBBValue<bool>(FName("bIsInit"), true);
		HyAIController->SetBBValue<bool>(FName("bCanAttack"), true);
	}
}

void UHyAction_AI_Spawn::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}

void UHyAction_AI_Spawn::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AI_Idle.h"

//#include "Character/NPCharacterNPC.h"
#include "AI/HyAIController.h"
#include "HyGameplayTags.h"
#include "HyTypes.h"


void UHyAction_AI_Idle::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);

	IdleWaitTime = 0.0f;

	//if (NPAIInterface)
	//{
	//	IdleWaitTime = NPAIInterface->GetAIWaitIdleTime();
	//}

	if (HyAIController)
	{
		HyAIController->SetBBValue<bool>(FName("bFinishIdleWait"), false);
		//HyAIController->SetBBValue<bool>(FName("bIsMovingObject"), NPAIInterface->IsMovingObject());
	}
}

void UHyAction_AI_Idle::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

	IdleWaitTime -= DeltaTime;

	if (IdleWaitTime < 0.f)
	{
		if (HyAIController)
		{
			HyAIController->SetBBValue<bool>(FName("bFinishIdleWait"), true);
		}
	}
}

void UHyAction_AI_Idle::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

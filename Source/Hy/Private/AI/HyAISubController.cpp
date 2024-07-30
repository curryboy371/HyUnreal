// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HyAISubController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AHyAISubController::AHyAISubController()
{
	const ConstructorHelpers::FObjectFinder<UBlackboardData> BBAsset_Ref(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/BehaviorTree/BB_Sub_Action.BB_Sub_Action'"));

	if (BBAsset_Ref.Object)
	{
		BBAsset = BBAsset_Ref.Object;
	}

	const ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAsset_Ref(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/BehaviorTree/BT_Sub_Action.BT_Sub_Action'"));
	if (BTAsset_Ref.Object)
	{
		BTAsset = BTAsset_Ref.Object;
	}
}

void AHyAISubController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
}

void AHyAISubController::OnUnPossess()
{
	Super::OnUnPossess();

	StopAI();
}

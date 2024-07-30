// Fill out your copyright notice in the Description page of Project Settings.



#include "AI/HyAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

#include "HyGameplayTags.h"

#include "Character/HyCharacter.h"


AHyAIController::AHyAIController()
{
	const ConstructorHelpers::FObjectFinder<UBlackboardData> BBAsset_Ref(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_Monster.BB_Monster'"));

	if(BBAsset_Ref.Object)
	{
		BBAsset = BBAsset_Ref.Object;
	}
	
	const ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAsset_Ref(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_Monster.BT_Monster'"));
	if(BTAsset_Ref.Object)
	{
		BTAsset = BTAsset_Ref.Object;
	}


	// Create AI Perception Component
	AIPerceptionCom = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionCom"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	//HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));

	InitAIPerception();

	// blackboard value name
	BBKeyActionHandler = FName("BBKeyActionHandler");
	BBKeyActionStarter = FName("BBKeyActionStarter");
	BBKeyActionStopper = FName("BBKeyActionStopper");
}

void AHyAIController::BeginPlay()
{
	Super::BeginPlay();


	InitActionHandler();
	StartAIPerception();
}

void AHyAIController::InitActionHandler()
{
	//FHyTags Taginstance = FHyTags::Get();
	//RegisterActionHandlers();
}

void AHyAIController::InitAIPerception()
{
	if (AIPerceptionCom == nullptr)
	{
		ERR_V("AIPerceptionCom is nullptr");
		return;
	}

	if (SightConfig == nullptr)
	{
		ERR_V("SightConfig is nullptr");
		return;
	}

	//if (HearingConfig == nullptr)
	//{
	//	ERR_V("HearingConfig is nullptr");
	//	return;
	//}

	SightConfig->SightRadius = 500.0f;
	SightConfig->LoseSightRadius = 700.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(0);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	//HearingConfig->HearingRange = 3000.0f;
	//HearingConfig->LoSHearingRange = 3500.0f;
	//HearingConfig->SetMaxAge(5.0f);
	//HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	//HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	//HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionCom->ConfigureSense(*SightConfig);
	//AIPerceptionCom->ConfigureSense(*HearingConfig);


}

void AHyAIController::SetOwnerCharacter(APawn* InPawn)
{
	OwnerCharacter = Cast<AHyCharacter>(InPawn);

	if (OwnerCharacter == nullptr)
	{
		ERR_V("Invalid Owner Character");
	}
}

void AHyAIController::StartAIPerception()
{
	if (AIPerceptionCom == nullptr)
	{
		ERR_V("AIPerceptionCom is nullptr");
		return;
	}

	if (SightConfig == nullptr)
	{
		ERR_V("SightConfig is nullptr");
		return;
	}

	//if (HearingConfig == nullptr)
	//{
	//	ERR_V("HearingConfig is nullptr");
	//	return;
	//}

	// 감지 시작

	AIPerceptionCom->OnPerceptionUpdated.AddDynamic(this, &AHyAIController::OnPerceptionUpdated);
	AIPerceptionCom->OnTargetPerceptionForgotten.AddDynamic(this, &AHyAIController::OnTargetPerceptionForgotten);
	AIPerceptionCom->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AHyAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if(UseBlackboard(BBAsset,BlackboardPtr))
	{
		Blackboard->SetValueAsVector(TEXT("HomePos"),GetPawn()->GetActorLocation());
		
		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void AHyAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if(BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AHyAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	//if (OwnerCharacter && OwnerCharacter->GetTar() == nullptr)
	//{
	//	for (auto PerceptedActor : UpdatedActors)
	//	{
	//		if (PerceptedActor)
	//		{
	//			WAR_V("Perception Update %s", *PerceptedActor->GetName())
	//			TObjectPtr<AHyCharacter> TargetCharacter = Cast<AHyCharacter>(PerceptedActor);
	//			if (TargetCharacter)
	//			{
	//				OwnerCharacter->SetTargetCharacter(TargetCharacter);
	//				WAR_V("Perception Update Set Target");
	//
	//			}
	//
	//		}
	//	}
	//}
}

void AHyAIController::OnTargetPerceptionForgotten(AActor* Actor)
{
	WAR_V("");

	//if (OwnerCharacter && OwnerCharacter->GetTargetCharacter())
	//{
	//	if (OwnerCharacter->GetTargetCharacter() == Actor)
	//	{
	//		OwnerCharacter->SetTargetCharacter(nullptr);
	//		WAR_V("Release Target");
	//
	//	}
	//}
}

void AHyAIController::AIActionHandleExit(const FGameplayTag& InActionTag, const EActionHandleExitType InHandleType)
{
	//FName BBKeyActionStarter; // Action 변경시 ON
	//FName BBKeyActionStopper; // Action 중지시 ON

	//switch (InHandleType)
	//{
	//case EActionHandleType::EActionTrigger:
	//	SetBBValue<FName>(BBKeyActionHandler, FName(InActionTag.ToString()));
	//	SetBBValue<bool>(BBKeyActionStarter, true);
	//	break;
	//case EActionHandleType::EActionStop:
	//	SetBBValue<FName>(BBKeyActionHandler, FName(InActionTag.ToString()));
	//	SetBBValue<bool>(BBKeyActionStopper, true);
	//	break;
	//case EActionHandleType::EActionFree:
	//	SetBBValue<FName>(BBKeyActionHandler, FName(InActionTag.ToString()));
	//	SetBBValue<bool>(BBKeyActionStopper, true);
	//	break;
	//case EActionHandleType::EActionSetStore:
	//	break;
	//default:
	//	break;
	//}

}

void AHyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	SetOwnerCharacter(InPawn);
	RunAI();
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "HyTypes.h"
#include "Action/HyActionTypes.h"
#include "HyAIController.generated.h"

/**
 * 
 */

UCLASS()
class HY_API AHyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AHyAIController();

	virtual void BeginPlay() override;

	void InitActionHandler();
	void InitAIPerception();

	void SetOwnerCharacter(APawn* InPawn);

	void StartAIPerception();


	void RunAI();
	void StopAI();





	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void OnTargetPerceptionForgotten(AActor* Actor);

public:
	/* 상태 패턴과 행동트리를 함께 사용하기 위해 BB를 AIController에서 세팅함*/

	void AIActionHandleExit(const FGameplayTag& InActionTag, const EActionHandleExitType InHandleType);

	template<typename T>
	void SetBBValue(const FName InKeyName, const FVector& InValue)
	{
		UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsVector(InKeyName, InValue);
		}
	}

	template<typename T>
	void SetBBValue(const FName InKeyName, const FString& InValue)
	{
		UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsString(InKeyName, InValue);
		}
	}

	template<typename T>
	void SetBBValue(const FName InKeyName, bool InValue)
	{
		UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsBool(InKeyName, InValue);
		}
	}

	template<typename T>
	void SetBBValue(const FName InKeyName, int32 InValue)
	{
		UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsInt(InKeyName, InValue);
		}
	}

	template<typename T>
	void SetBBValue(const FName InKeyName, float InValue)
	{
		UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsFloat(InKeyName, InValue);
		}
	}

	template<typename T>
	void SetBBValue(const FName InKeyName, const FRotator& InValue)
	{
		UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsRotator(InKeyName, InValue);
		}
	}

	template<typename T>
	void SetBBValue(const FName InKeyName, const FName& InValue)
	{
		UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsName(InKeyName, InValue);
		}
	}

	template<typename T>
	void SetBBValue(const FName InKeyName, UObject* InValue)
	{
		UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsObject(InKeyName, InValue);
		}
	}

protected:
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HY | AIPerception")
	TObjectPtr<class UAIPerceptionComponent> AIPerceptionCom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HY | AIPerception")
	TObjectPtr<class UAISenseConfig_Sight> SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HY | AIPerception")
	TObjectPtr<class UAISenseConfig_Hearing> HearingConfig;

	//UPROPERTY()
	//TMap<FGameplayTag, TMap<EActionHandleType, ActionHandlerFunc>> ActionHandlers;

	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;
	
	UPROPERTY()
	TObjectPtr<class AHyCharacter> OwnerCharacter;

	FName BBKeyActionHandler; // 변경할 Action 
	FName BBKeyActionStarter; // Action 변경시 ON
	FName BBKeyActionStopper; // Action 중지시 ON
};

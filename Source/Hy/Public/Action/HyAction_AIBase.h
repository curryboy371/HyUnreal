// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyActionBase.h"
#include "HyAction_AIBase.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyAction_AIBase : public UHyActionBase
{
	GENERATED_BODY()
	
public:
	UHyAction_AIBase();
public:
	virtual void OnActionStarted_Implementation(const FString& contextString = "");
	virtual void OnTick_Implementation(float DeltaTime);
	virtual void OnActionEnded_Implementation();

protected:
	virtual void SetNextAction() {};
	virtual void StopCurAction() {};


protected:
	TObjectPtr<class AHyAIController> HyAIController;
	//class INPCharacterAIInterface* NPAIInterface;

	bool bIsFollowObject = false;
	
};

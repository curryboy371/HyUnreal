// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyAction_AIBase.h"
#include "HyAction_AI_Idle.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyAction_AI_Idle : public UHyAction_AIBase
{
	GENERATED_BODY()
	
public:
	virtual void OnActionStarted_Implementation(const FString& contextString = "");
	virtual void OnTick_Implementation(float DeltaTime);
	virtual void OnActionEnded_Implementation();


protected:
	float IdleWaitTime;
};

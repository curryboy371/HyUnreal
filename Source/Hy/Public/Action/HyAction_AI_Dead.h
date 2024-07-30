// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyAction_AIBase.h"
#include "HyAction_AI_Dead.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyAction_AI_Dead : public UHyAction_AIBase
{
	GENERATED_BODY()
public:
	virtual void OnActionStarted_Implementation(const FString& contextString = "") override;
	virtual void OnActionSetupCompleted_Implementation(const FString& contextString = "") override;
	virtual void OnTick_Implementation(float DeltaTime) override;
	virtual void OnActionEnded_Implementation() override;
	

public:
	void PauseDeadAnim();

protected:
	bool bIsPause = false;
};

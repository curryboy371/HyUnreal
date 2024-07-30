// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyAction_AI_ComboBase.h"
#include "HyAction_AI_NormalAttack.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyAction_AI_NormalAttack : public UHyAction_AI_ComboBase
{
	GENERATED_BODY()
	
public:
	virtual void OnActionStarted_Implementation(const FString& contextString = "") override;
	virtual void OnActionEnded_Implementation() override;
	virtual void OnActionTransition_Implementation(class UHyActionBase* previousState) override;

	virtual bool IsStopConditional_Implementation();

	
};

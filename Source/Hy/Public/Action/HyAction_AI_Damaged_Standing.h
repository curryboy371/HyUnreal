// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyAction_AI_DamagedBase.h"
#include "HyAction_AI_Damaged_Standing.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyAction_AI_Damaged_Standing : public UHyAction_AI_DamagedBase
{
	GENERATED_BODY()
	
public:
	virtual void OnActionStarted_Implementation(const FString& contextString = "");
	virtual void OnActionTransition_Implementation(class UHyActionBase* previousState) override;
	virtual void OnTick_Implementation(float DeltaTime);
	virtual void OnActionEnded_Implementation();
	
	
};

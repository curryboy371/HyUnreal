// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyActionComboBase.h"
#include "HyAction_NormalAttack.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyAction_NormalAttack : public UHyActionComboBase
{
	GENERATED_BODY()
	
public:
	virtual void OnActionStarted_Implementation(const FString& contextString = "") override;
	virtual void OnActionEnded_Implementation() override;
	virtual void OnActionTransition_Implementation(class UHyActionBase* previousState) override;
	virtual bool IsStopConditional_Implementation();
	
protected:
	void SetOwnerCharacterRotation();


};

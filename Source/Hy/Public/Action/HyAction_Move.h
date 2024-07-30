// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyActionBase.h"
#include "HyAction_Move.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyAction_Move : public UHyActionBase
{
	GENERATED_BODY()
	
public:
	virtual void OnActionEnded_Implementation();
	
};

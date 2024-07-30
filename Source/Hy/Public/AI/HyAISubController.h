// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HyAIController.h"
#include "HyAISubController.generated.h"

/**
 * 
 */
UCLASS()
class HY_API AHyAISubController : public AHyAIController
{
	GENERATED_BODY()
	
public:
	AHyAISubController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

};

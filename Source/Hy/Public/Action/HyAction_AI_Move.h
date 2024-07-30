// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyAction_AIBase.h"
#include "Character/HyCombatTypes.h"
#include "HyAction_AI_Move.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyAction_AI_Move : public UHyAction_AIBase
{
	GENERATED_BODY()
public:
	virtual void OnActionStarted_Implementation(const FString& contextString = "");
	virtual void OnTick_Implementation(float DeltaTime);
	virtual void OnActionEnded_Implementation();
	
protected:
	void ArrivalAtDestination();
	void MoveRetry();

	const bool ShouldRetryMove();

	bool FindMoveDestination();
	bool IsAtDestination();
	void RetryMoveDest();



	void DebugDrawMoveArrow();

protected:
	EAIMoveType LastAIMoveType = EAIMoveType::EAIMove_None;
	int32 RetryMoveCount = 0;

	bool IsWalkMode = true;

	bool bHasDestination = false;

	float ToleranceDistance;

};

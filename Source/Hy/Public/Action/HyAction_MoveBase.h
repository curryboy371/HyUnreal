// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyActionBase.h"
#include "HyAction_MoveBase.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyAction_MoveBase : public UHyActionBase
{
	GENERATED_BODY()

public:
	virtual void OnActionStarted_Implementation(const FString& contextString = "");
	virtual void OnTick_Implementation(float DeltaTime);
	virtual void OnActionEnded_Implementation();
	virtual bool IsStopConditional_Implementation();

protected:
	FVector DashDirection;
	FVector StartLocation;
	FVector DestLocation;
	FVector DashVelocity;

	bool bStopAction = false;
	bool bStopMove = false;
	bool bIsAtDestination = false;

	float KeekDashVelocityAngle = 15.f;
	
	
};

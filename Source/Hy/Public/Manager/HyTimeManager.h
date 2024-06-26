// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/HyManagerBase.h"
#include "TimerManager.h"

#include "HyTimeManager.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyTimeManager : public UHyManagerBase
{
	GENERATED_BODY()
	
public:
	virtual void InitManager() {};
	virtual void ReleaseManager() {};
	virtual void UpdateManager(float DeltaTime) {};
	

public:
	void SetTimerFunc(float Delay, TFunction<void()> FunctionToCall);
	

private:
	// 타이머 핸들
	FTimerHandle TimerHandle;
};

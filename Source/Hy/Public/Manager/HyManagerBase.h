// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HyTypes.h"

#include "HyManagerBase.generated.h"

/**
 * 
 */
UCLASS(abstract)
class HY_API UHyManagerBase : public UObject
{
	GENERATED_BODY()

public:
	// FObjectInitializer를 사용하는 생성자
	UHyManagerBase(const FObjectInitializer& ObjectInitializer);

	virtual void InitManager() {};
	virtual void ReleaseManager() {};

public:
	GETTER(EManagerNum, ManagerNum);
	SETTER(EManagerNum, ManagerNum);

protected:
	EManagerNum ManagerNum;
};

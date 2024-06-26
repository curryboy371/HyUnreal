// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/HyManagerBase.h"

#include "Protocol.pb.h"

#include "HyDataManager.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyDataManager : public UHyManagerBase
{
	GENERATED_BODY()
public:
	UHyDataManager(const FObjectInitializer& ObjectInitializer);


private:
	Protocol::hyps_user_info MyUserInfo;
	Protocol::hyps_object_info MyPlayerInfo;
};

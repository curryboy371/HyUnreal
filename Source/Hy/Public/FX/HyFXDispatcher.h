// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HyTypes.h"
#include "HyFXTypes.h"

#include "HyFXDispatcher.generated.h"

/**
 * 
 
 전역에서 FX를 생성하는 class
 
 */
UCLASS()
class HY_API UHyFXDispatcher : public UObject
{
	GENERATED_BODY()
	
public:
	void PlayActionFX(const FHyActionEffect& effect, class ACharacter* instigator);

	FAttachedComponents SpawnFXAttached(const FHyActionEffect& effect, class ACharacter* instigator);
private:
	void SpawnFXAtLocation(const FDispatchFX& effect);


	void Internal_PlayEffect(class ACharacter* instigator, const FHyActionEffect& effect);

private:
	TMap<FGuid, FAttachedComponents> ActiveFXMap;
};



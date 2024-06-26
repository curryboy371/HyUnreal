// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "HyGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	
};

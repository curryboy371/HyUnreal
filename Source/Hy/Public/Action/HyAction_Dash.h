// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyAction_MoveBase.h"
#include "HyAction_Dash.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyAction_Dash : public UHyAction_MoveBase
{
    GENERATED_BODY()

public:
    virtual void OnActionStarted_Implementation(const FString& contextString = "");
    virtual void OnTick_Implementation(float DeltaTime);
    virtual void OnActionEnded_Implementation();
    virtual bool IsStopConditional_Implementation();

protected:
    bool bMoveStop = false;

};

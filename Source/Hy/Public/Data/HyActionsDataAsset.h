// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Action/HyActionTypes.h"
#include "GameplayTagContainer.h"

#include "HyActionsDataAsset.generated.h"

/**
 * 
 * 
 * 
 */
UCLASS()
class HY_API UHyActionsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	void AddOrModifyAction(const FHyActionState& InAction);
	bool GetActionByTag(const FGameplayTag& InTag, FHyActionState& OutAction) const;

	void GetActions(TArray<FHyActionState>& OutActions) const {	OutActions = Actions; }

protected:
	UPROPERTY(EditAnywhere, meta = (TitleProperty = "TagName"), BlueprintReadWrite, Category = "Hy | Actions")
	TArray<FHyActionState> Actions;
};

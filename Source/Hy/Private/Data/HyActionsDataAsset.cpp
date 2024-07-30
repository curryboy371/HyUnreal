// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/HyActionsDataAsset.h"

void UHyActionsDataAsset::AddOrModifyAction(const FHyActionState& InAction)
{
	if (Actions.Contains(InAction.TagName))
	{
		Actions.Remove(InAction);
	}
	Actions.AddUnique(InAction);
}

bool UHyActionsDataAsset::GetActionByTag(const FGameplayTag& InTag, FHyActionState& OutAction) const
{
	const FHyActionState* actionState = Actions.FindByKey(InTag);
	if (actionState) 
	{
		OutAction = *actionState;
		return true;
	}
	return false;
}

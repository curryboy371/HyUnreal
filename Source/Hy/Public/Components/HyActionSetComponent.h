// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Action/HyActionBase.h"

#include "Action/HyActionTypes.h"
#include "Data/HyActionsDataAsset.h"

#include "GameplayTagContainer.h"
#include "HyActionSetComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionStarted, FGameplayTag, ActionState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionEnded, FGameplayTag, ActionState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionTriggered, FGameplayTag, ActionState, EActionPriority, Priority);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HY_API UHyActionSetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHyActionSetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PlayMontage(const FHyMontageInfo& montageInfo, float StartFrame);

	void LaunchAction(const FGameplayTag& ActionState, const EActionPriority priority, const FString contextString = TEXT(""));

	void FreeAction();

	void SetCurrentAction(const FGameplayTag& ActionState);

	UFUNCTION(BlueprintCallable, Category = HY)
	void StoreAction(FGameplayTag Action, const FString& contextString = TEXT(""), const int32 InStorePriority = 0);

	void ActionStart(const FGameplayTag& ActionState, const FString& contextString);
	void ActionEnd(const FGameplayTag& ActionState);
	void ActionStopImmeditaley(float InBlendOutTime = 0.0f);
	void PauseAction(bool bSetPause);

	void ClearPerformingActionState();

	void SetPerformingActionPriority(EActionPriority Priority);


	bool IsActionStopCondition();

	TObjectPtr<class UHyActionBase> GetCurrentAction(const FGameplayTag& ActionState);
	TObjectPtr<class UAnimMontage>  GetCurrentMontage(const FGameplayTag& ActionState);
	
	/* 제공된 태그로 행동을 트리거하려고 시도합니다. 이 행동의 우선순위는 나중에 더 낮은 우선순위의 행동을 중단하는 데 사용됩니다.
   만약 `bCanBeStored`가 true로 설정되어 있고, 행동이 즉시 실행될 수 없다면, 현재 행동이 끝날 때 저장되고 다시 트리거됩니다.
   `Context String`은 `OnActionStarted` 이벤트로 전달되며, 이를 통해 행동에 일반적인 데이터를 전달할 수 있습니다.
	*/
	UFUNCTION(BlueprintCallable, Category = HY)
	void TriggerAction(FGameplayTag ActionState, EActionPriority Priority = EActionPriority::ELow, bool bCanBeStored = false, const FString& contextString = "");

	void SetStoredActionTag(FGameplayTag ActionState, EActionPriority Priority = EActionPriority::ELow, bool bForce = false, const FString contextString = "");
	void SetDefaultStoredActionTag(const bool bForce = false);

	void SetTagActionRate(const FGameplayTag& ActionState,float Reta);

	UFUNCTION(BlueprintCallable, Category = HY)
	bool CanExecuteAction(FGameplayTag ActionTag) const;
	
	void InternalExitAction();
	void TerminateCurrentAction();


	UFUNCTION(BlueprintCallable, Category = HY)
	void SetMovesetActions(const FGameplayTag& movesetActionsTag);

	UFUNCTION(BlueprintCallable, Category = HY)
	bool GetActionByTag(const FGameplayTag& Action, FHyActionState& outAction) const;

	UFUNCTION(BlueprintCallable, Category = HY)
	bool GetMovesetActionByTag(const FGameplayTag& action, const FGameplayTag& Moveset, FHyActionState& outAction) const;

	UFUNCTION(BlueprintCallable, Category = HY)
	bool GetCommonActionByTag(const FGameplayTag& action, FHyActionState& outAction) const;

	UFUNCTION(BlueprintCallable, Category = HY)
	const FGameplayTag GetPerformingActionTag() const;

	UFUNCTION(BlueprintCallable, Category = HY)
	const FGameplayTag GetStoredActionTag() const;
	

	const bool IsDefaultStoredAction() const;
	const bool IsEmptyStoredAction() const;

	const bool IsLastMonstageSection() const;

protected:
	void ResetActionState();

public:
	UPROPERTY()
	TObjectPtr<class UHyAnimInstance> animInst;

	UPROPERTY(BlueprintAssignable, Category = HY)
	FOnActionStarted OnActionStarted;

	UPROPERTY(BlueprintAssignable, Category = HY)
	FOnActionEnded OnActionFinished;
	
	UPROPERTY(BlueprintAssignable, Category = HY)
	FOnActionTriggered OnActionTriggered;

	/* Moveset과 관계없이 공통으로 계속 사용하게될 ActionDataSet*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = HY)
	TSubclassOf<UHyActionsDataAsset> ActionsDataSet;

	/*	교체 하여 사용하는 ActionDataSet
		currentMovesetActionsTag 과 일치하는 ActionSet만 사용 가능	
	*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (TitleProperty = "TagName"), Category = HY)
	TArray<FHyActionsSet> MovesetActions;

	/* ActionsDataSet을 Runtime에서 instance화 하여 사용함 */
	UPROPERTY(BlueprintReadOnly, Category = HY)
	TObjectPtr<UHyActionsDataAsset> ActionsDataSetInst;

	/* MovesetActions을 Runtime에서 instance화 하여 사용함 */
	UPROPERTY(BlueprintReadOnly, Category = HY)
	TMap<FGameplayTag, TObjectPtr<UHyActionsDataAsset>> MovesetsActionsInst;


	UPROPERTY(BlueprintReadOnly, Category = HY)
	TObjectPtr<class AHyCharacter> CharacterOwner;

	UPROPERTY(BlueprintReadOnly, Category = HY)
	FHyMontageInfo MontageInfo;

	/* Action State Values */

	/* Action Tag */
	FGameplayTag CurrentActionTag;
	FGameplayTag StoredAction;

	/* Action 우선순위 */
	int32 CurrentPriority;
	int32 StoredPriority;

	/* Action에 전달할 Flag 용도의 String */
	FString CurrentString;
	FString StoredString;

	const int32 EmptyPriority = -1;

	/* 현재 상태에 맞는 MovesetsActionsInst Set를 결정짓는 Tag*/
	FGameplayTag currentMovesetActionsTag;


	bool bIsPerformingAction;


	TObjectPtr<UHyActionBase> PerformingAction;

};

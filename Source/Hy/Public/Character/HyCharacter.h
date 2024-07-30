// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Hy.h"

#include "HyCharacter.generated.h"

UCLASS()
class HY_API AHyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHyCharacter();

	virtual ~AHyCharacter();


protected:
	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;

	//UFUNCTION(BlueprintCallable)
	//void SaveColliderInfo();

#endif

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void PlayAttachEffect(FHyActionEffect& InEffect);
	void StopAttachEffect(FHyActionEffect& InEffect);

	void HandleActionExit(EActionHandleExitType ExitType, float BlendOut = 0.5f);

	virtual void TriggerAction(FGameplayTag InActionTag, EActionPriority Priority = EActionPriority::ELow, bool bCanbeStore = false, const FString contextString = TEXT("")) {};
	virtual void SetStoredAction(FGameplayTag InActionTag, EActionPriority Priority = EActionPriority::ELow, bool bForce = false, const FString contextString = TEXT("")) {};

	void SetPerformingActionPriority(EActionPriority Priority);
	void SetDefaultStoredAction(const bool bForce = false);
	const bool IsDefaultStoredAction() const;
	const bool IsEmptyStoredAction() const;
	const bool IsCanStoreAction(EActionPriority InPriority) const;

	FGameplayTag GetPerformingActionTag();
	const FGameplayTag GetStoredActionTag();

	const FGameplayTag& GetCharacterTag() { return CharacterTag; }
	const FGameplayTag& GetCurMovesetTag() { return MoveActionSetTag; };

	EControlPlayer GetControlPlayer() { return thisPlayer; }
	const int32 GetCharacterID() { return CharacterID; }


	float PlayAnimMontage_Custom(class UAnimMontage* AnimMontage, float InPlayRate, EMontageBlendType BlendType, FName StartSectionName, float TimeToStartMontageAt = 0.0f);
	void PauseAction(bool bSetPause);

public:


protected:



	// FX
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HY | Component", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHyFXComponent> FXComponent;

	// Action
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HY | Component", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHyActionSetComponent> ActionSetComponent;

	//MotionWarping
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HY | Component", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMotionWarpingComponent> MotionWarpingCom;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveOption, meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterState, FCharacterMoveOption> CharacterMoveOptionMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	EEquippedWeaponState EquippedWeaponState;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	ECharacterState CharacterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HY | Info", Meta = (AllowPrivateAccess = "true"))
	EControlPlayer thisPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HY | Info", Meta = (AllowPrivateAccess = "true"))
	FGameplayTag CharacterTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HY | Action", Meta = (AllowPrivateAccess = "true"))
	FGameplayTag MoveActionSetTag; // 액션세트 태그


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HY | Info", Meta = (AllowPrivateAccess = "true"))
	int32 CharacterID;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HY | Dash", Meta = (AllowPrivateAccess = "true"))
	bool bIsInputMoving = false; // moveinput이 입력되는 중인지


	FGuid MyGuid;
	FGuid TargetGuid;



	bool bIsDead = false;
	bool bIsInit = false;


public:
	void SetDesiredPosInfo(const Protocol::hyps_pos_info& InDesiredPosInfoRef);
	void SetDesiredPosInfo(const FVector& InPosInfo, const float InYaw, Protocol::hype_move_state InMoveState);
	void SetPosInfo(const FVector& InPosInfo, const float InYaw, Protocol::hype_move_state InMoveState);

	GETTER(int64, ObjectID)
	SETTER(int64, ObjectID)

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	int64 ObjectID;

	Protocol::hyps_pos_info* PosInfo;
	Protocol::hyps_pos_info* DesiredPosInfo;
};

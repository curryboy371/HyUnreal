// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Hy.h"
#include "HyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

protected:
	UFUNCTION(BlueprintCallable)
	UHyAnimInstance* GetOwningAnimInstance();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))

	EEquippedWeaponState EquippedWeaponState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))

	ELocomotionDirection LocomotionDirection;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim, meta = (AllowPrivateAccess = "true"))
	FDirectionalAnimations WalkCycleAnims;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim, meta = (AllowPrivateAccess = "true"))
	FDirectionalAnimations JogCycleAnims;
};

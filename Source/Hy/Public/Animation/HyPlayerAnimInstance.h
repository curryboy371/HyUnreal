// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/HyAnimInstance.h"

#include "Animation/HyAnimationTypes.h"

#include "HyPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyPlayerAnimInstance : public UHyAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Anim", meta = (AllowPrivateAccess = "true"))
	FCycleAnimSet WalkAnimSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Anim", meta = (AllowPrivateAccess = "true"))
	FCycleAnimSet RunAnimSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Anim", meta = (AllowPrivateAccess = "true"))
	FDirectionalTurnAnim DiretionalTurnAnimSet;
};

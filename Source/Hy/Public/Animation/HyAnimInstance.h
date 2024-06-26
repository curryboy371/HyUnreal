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
	
public:
	UHyAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintPure, Category = "Animation", meta = (BlueprintThreadSafe))
	const bool IsMaxSpeed() const;

	UFUNCTION(BlueprintPure, Category = "Animation", meta = (BlueprintThreadSafe))
	const bool IsCanStop() const { return (!bIsAccelerating && bIsZeroVelocity); } // 움직임과 가속이 모두 없음

	UFUNCTION(BlueprintCallable, Category = "Animation")
	UHyAnimInstance* GetOwningAnimInstance() const;

protected:
	UFUNCTION(BlueprintCallable, Category = "UpdateData", meta = (BlueprintThreadSafe))
	void UpdateOwnerData();

	UFUNCTION(BlueprintCallable, Category = "UpdateData", meta = (BlueprintThreadSafe))
	ELocomotionDirection CalculationLocomotionDirection(float CurAngle, ELocomotionDirection CurDirection, FVector2D BackwardRange, FVector2D ForwardRange, float DeadZone);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	EEquippedWeaponState EquippedWeaponState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	ECharacterState IncommingCharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	ECharacterState CharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	ECharacterState LastFrameCharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool bChangeCharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	ELocomotionDirection LocomotionDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	ELocomotionDirection LastFrameLocomotionDirection;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	FVector WorldLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	FVector LastWorldLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	float LocationDelta;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	FVector CharacterVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	FVector CharacterVelocity2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	bool bIsZeroVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	FVector Acceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	FVector Acceleration2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	float JumpApexTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	float GroundDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	bool bIsJumping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	bool bIsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	bool bIsOnAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	bool bIsRotating;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	FRotator WorldRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	float VelocityAngle;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim, meta = (AllowPrivateAccess = "true"))
	UAnimSequence* IdleAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim, meta = (AllowPrivateAccess = "true"))
	FDirectionalAnimations WalkCycleAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim, meta = (AllowPrivateAccess = "true"))
	FDirectionalAnimations JogCycleAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim, meta = (AllowPrivateAccess = "true"))
	FDirectionalAnimations JogStopAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim, meta = (AllowPrivateAccess = "true"))
	FDirectionalAnimations WalkStopAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim, meta = (AllowPrivateAccess = "true"))
	FDirectionalAnimations JogStartAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim, meta = (AllowPrivateAccess = "true"))
	FDirectionalAnimations WalkStartAnims;

};

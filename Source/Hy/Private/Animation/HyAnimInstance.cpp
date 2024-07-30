// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimInstance.h"
#include "GameFramework/Character.h" // For ACharacter class
#include "Components/SkeletalMeshComponent.h" // For USkeletalMeshComponent class

#include "GameFramework/CharacterMovementComponent.h"

#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"

UHyAnimInstance::UHyAnimInstance()
	:CharacterMovementComponent(nullptr), CharacterState(ECharacterState::Idle)
{

}

void UHyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	LOG_I;
	if (AActor* OwningActor = GetOwningActor())
	{
		ACharacter* OwningCharacter = Cast<ACharacter>(OwningActor);

		if (OwningCharacter)
		{
			CharacterMovementComponent = OwningCharacter->GetCharacterMovement();

			if(CharacterMovementComponent)
			{
				LOG_V("CharacterMovementComponent bind Success");
			}
		}
	}
}

const bool UHyAnimInstance::IsMaxSpeed() const
{
	if (CharacterMovementComponent)
	{
		return FMath::IsNearlyEqual(CharacterVelocity2D.Length(), CharacterMovementComponent->MaxWalkSpeed, 0.0001f);
	}
	return false;
}

UHyAnimInstance* UHyAnimInstance::GetOwningAnimInstance() const
{
	if (AActor* OwningActor = GetOwningActor())
	{
		ACharacter* OwningCharacter = Cast<ACharacter>(OwningActor);

		if (OwningCharacter)
		{
			if (UAnimInstance* AnimInstance = OwningCharacter->GetMesh()->GetAnimInstance())
			{
				UHyAnimInstance* OwningAnimInstance = Cast<UHyAnimInstance>(AnimInstance);
				if (OwningAnimInstance)
				{
					return OwningAnimInstance;
				}
			}
		}
	}

	return nullptr;
}

void UHyAnimInstance::UpdateOwnerData()
{
	if (nullptr == CharacterMovementComponent)
	{
		return;
	}

	FVector Vector2D = FVector(1.f, 1.f, 0.f);

	if (AActor* OwningActor = GetOwningActor())
	{
		// Set Location, Rotation
		LastWorldLocation = WorldLocation;
		WorldLocation = OwningActor->GetActorLocation();
		LocationDelta = (WorldLocation - LastWorldLocation).Length();


		WorldRotation = OwningActor->GetActorRotation();

		// Set character state
		LastFrameCharacterState = CharacterState;
		CharacterState = IncommingCharacterState;
		bChangeCharacterState = (CharacterState != LastFrameCharacterState) ? true : false;

		// Set Accelation 
		Acceleration = CharacterMovementComponent->GetCurrentAcceleration();
		Acceleration2D = Vector2D * Acceleration;
		bIsAccelerating = !FMath::IsNearlyEqual(Acceleration2D.Length(), 0.0f, 0.0001f);

		// Set Velocity
		CharacterVelocity = CharacterMovementComponent->Velocity;
		CharacterVelocity2D = FVector(1.f, 1.f, 0.f) * CharacterVelocity;
		bIsZeroVelocity = FMath::IsNearlyEqual(CharacterVelocity2D.Length(), 0.0f, 0.0001f);

		// Set Pivot
		LastPivotDot = PivotDot;

		FVector NormalVelocity = CharacterVelocity2D.GetSafeNormal();
		FVector NormalAcceleration = Acceleration2D.GetSafeNormal();
		PivotDot = NormalVelocity.Dot(NormalAcceleration);

		// Set Direction, Angle
		LastFrameLocomotionDirection = LocomotionDirection;
		VelocityAngle = UKismetAnimationLibrary::CalculateDirection(CharacterVelocity2D, WorldRotation);
		AccelerationAngle = UKismetAnimationLibrary::CalculateDirection(Acceleration2D, WorldRotation);


		FVector2D BackRange = { -130, 130 };
		FVector2D LeftRange = { -130, -50 };
		FVector2D RightRange = { 50, 130 };
		FVector2D FowardRange = { -50, 50 };
		LocomotionDirection = CalculationLocomotionDirection(VelocityAngle, LocomotionDirection, BackRange, FowardRange, 20.f);
		AccelerationLocomotionDirection = CalculationLocomotion4Direction(AccelerationAngle, AccelerationLocomotionDirection, BackRange, FowardRange, 20.f);


		bIsOnAir = CharacterMovementComponent->MovementMode == EMovementMode::MOVE_Falling;

		// 점프중
		bIsJumping = CharacterVelocity.Z > 0.f && bIsOnAir;

		// 낙하중
		bIsFalling = CharacterVelocity.Z < 0.f && bIsOnAir;

		// 점프 최고점 시간 계산
		float CharacterVerticalVelocity = 0 - CharacterVelocity.Z;

		// 캐릭터의 중력 및 중력 스케일
		float GravityZ = CharacterMovementComponent->GetGravityZ();
		float GravityScale = CharacterMovementComponent->GravityScale;

		// 점프의 최고점에 도달하는데 걸리는 시간
		if(bIsJumping)
		{
			JumpApexTime = CharacterVerticalVelocity / (GravityZ * GravityScale);
		}
		else
		{
			JumpApexTime = 0.f;
		}
	}

}

ELocomotionDirection UHyAnimInstance::CalculationLocomotionDirection(float CurAngle, ELocomotionDirection CurDirection, FVector2D BackwardRange, FVector2D ForwardRange, float DeadZone)
{

	// deadzone check
	// FVector2D X Min, Y Max
	switch (CurDirection)
	{
	case ELocomotionDirection::F_0:
	{
		float Min = ForwardRange.X - DeadZone;
		float Max = ForwardRange.Y + DeadZone;

		if (UKismetMathLibrary::InRange_FloatFloat(CurAngle, Min, Max))
		{
			return ELocomotionDirection::F_0;
		}
	}

		break;
	case ELocomotionDirection::B_180:
	{
		if (CurAngle < BackwardRange.X + DeadZone || CurAngle > BackwardRange.Y - DeadZone)
		{
			return ELocomotionDirection::B_180;
		}
	}
		break;
	case ELocomotionDirection::FR_90:
	case ELocomotionDirection::BR_90:
	{
		float Min = ForwardRange.Y - DeadZone;
		float Max = BackwardRange.Y + DeadZone;

		if (UKismetMathLibrary::InRange_FloatFloat(CurAngle, Min, Max))
		{
			return ELocomotionDirection::FR_90;
		}

	}
		break;
	case ELocomotionDirection::FL_90:
	case ELocomotionDirection::BL_90:
	{
		float Min = BackwardRange.X - DeadZone;
		float Max = ForwardRange.X + DeadZone;

		if (UKismetMathLibrary::InRange_FloatFloat(CurAngle, Min, Max))
		{
			return ELocomotionDirection::FL_90;
		}

	}
		break;
	default:
		break;
	}

	if (CurAngle < BackwardRange.X || CurAngle > BackwardRange.Y)
	{
		return ELocomotionDirection::B_180;
	}
	else
	{
		float Min = ForwardRange.X;
		float Max = ForwardRange.Y;
		if (UKismetMathLibrary::InRange_FloatFloat(CurAngle, Min, Max))
		{
			return ELocomotionDirection::F_0;
		}
		else
		{
			if (CurAngle > 0.f)
			{
				return ELocomotionDirection::FR_90;

			}
			else
			{
				return ELocomotionDirection::FL_90;
			}
		}
	}
}

ELocomotion4Direction UHyAnimInstance::CalculationLocomotion4Direction(float CurAngle, ELocomotion4Direction CurDirection, FVector2D BackwardRange, FVector2D ForwardRange, float DeadZone)
{
	// deadzone check
// FVector2D X Min, Y Max
	switch (CurDirection)
	{
	case ELocomotion4Direction::F_0:
	{
		float Min = ForwardRange.X - DeadZone;
		float Max = ForwardRange.Y + DeadZone;

		if (UKismetMathLibrary::InRange_FloatFloat(CurAngle, Min, Max))
		{
			return ELocomotion4Direction::F_0;
		}
	}

	break;
	case ELocomotion4Direction::B_180:
	{
		if (CurAngle < BackwardRange.X + DeadZone || CurAngle > BackwardRange.Y - DeadZone)
		{
			return ELocomotion4Direction::B_180;
		}
	}
	break;
	case ELocomotion4Direction::R_90:
	{
		float Min = ForwardRange.Y - DeadZone;
		float Max = BackwardRange.Y + DeadZone;

		if (UKismetMathLibrary::InRange_FloatFloat(CurAngle, Min, Max))
		{
			return ELocomotion4Direction::R_90;
		}

	}
	break;
	case ELocomotion4Direction::L_90:
	{
		float Min = BackwardRange.X - DeadZone;
		float Max = ForwardRange.X + DeadZone;

		if (UKismetMathLibrary::InRange_FloatFloat(CurAngle, Min, Max))
		{
			return ELocomotion4Direction::L_90;
		}

	}
	break;
	default:
		break;
	}

	if (CurAngle < BackwardRange.X || CurAngle > BackwardRange.Y)
	{
		return ELocomotion4Direction::B_180;
	}
	else
	{
		float Min = ForwardRange.X;
		float Max = ForwardRange.Y;
		if (UKismetMathLibrary::InRange_FloatFloat(CurAngle, Min, Max))
		{
			return ELocomotion4Direction::F_0;
		}
		else
		{
			if (CurAngle > 0.f)
			{
				return ELocomotion4Direction::R_90;

			}
			else
			{
				return ELocomotion4Direction::L_90;
			}
		}
	}
}

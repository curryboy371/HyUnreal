// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimInstance.h"
#include "GameFramework/Character.h" // For ACharacter class
#include "Components/SkeletalMeshComponent.h" // For USkeletalMeshComponent class

#include "GameFramework/CharacterMovementComponent.h"

#include "Math/UnrealMathUtility.h"

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
	if (AActor* OwningActor = GetOwningActor())
	{
		WorldLocation = OwningActor->GetActorLocation();
		WorldRotation = OwningActor->GetActorRotation();

	}


	// character state
	LastFrameCharacterState = CharacterState;
	CharacterState = IncommingCharacterState;
	bChangeCharacterState = (CharacterState != LastFrameCharacterState) ? true : false;

	//AccelationData
	Acceleration = CharacterMovementComponent->GetCurrentAcceleration();
	Acceleration2D = FVector(1.f, 1.f, 0.f) * Acceleration;



	// 
	// velocity 
	// movement
	if (CharacterMovementComponent)
	{
		CharacterVelocity = CharacterMovementComponent->Velocity;
		CharacterVelocity2D = FVector(1.f, 1.f, 0.f) * CharacterVelocity;
		bIsAccelerating = !FMath::IsNearlyEqual(CharacterVelocity2D.Length(), 0.0f, 0.0001f);


	}



	// rotation
		// get actor rotation 

	// rorientation

	// direction

	// acceleration

	// character state


	if (AActor* OwningActor = GetOwningActor())
	{

		OwningActor->GetMove
		ACharacter* OwningCharacter = Cast<ACharacter>(OwningActor);



	}

}

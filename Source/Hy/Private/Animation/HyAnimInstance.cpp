// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimInstance.h"
#include "GameFramework/Character.h" // For ACharacter class
#include "Components/SkeletalMeshComponent.h" // For USkeletalMeshComponent class

UHyAnimInstance* UHyAnimInstance::GetOwningAnimInstance()
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

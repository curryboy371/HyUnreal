// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "HyCharacter.h"
#include "Math/UnrealMathUtility.h"

#include "Components/HyFXComponent.h"
#include "Components/HyActionSetComponent.h"


// Sets default values
AHyCharacter::AHyCharacter()
{
	PosInfo = new Protocol::hyps_pos_info;
	DesiredPosInfo = new Protocol::hyps_pos_info;


	CharacterState = ECharacterState::Idle;
	EquippedWeaponState = EEquippedWeaponState::UnArmed;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

}

void AHyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// 컴포넌트 초기화
}

AHyCharacter::~AHyCharacter()
{
	if (PosInfo)
	{
		delete PosInfo;
		PosInfo = nullptr;
	}

	if (DesiredPosInfo)
	{
		delete DesiredPosInfo;
		DesiredPosInfo = nullptr;
	}
}

// Called when the game starts or when spawned
void AHyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (DesiredPosInfo)
	{
		DesiredPosInfo->set_x(0);
		DesiredPosInfo->set_y(0);
		DesiredPosInfo->set_z(0);
		DesiredPosInfo->set_yaw(GetActorRotation().Yaw);
		DesiredPosInfo->set_move_state(Protocol::hype_move_state::move_state_none);
	}
	
	if (PosInfo)
	{
		const FVector& LocationRef = GetActorLocation();
		PosInfo->set_x(LocationRef.X);
		PosInfo->set_y(LocationRef.Y);
		PosInfo->set_z(LocationRef.Z);
		PosInfo->set_yaw(GetActorRotation().Yaw);
		PosInfo->set_move_state(Protocol::hype_move_state::move_state_none);
	}

}

#if WITH_EDITOR
void AHyCharacter::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

}
#endif


// Called every frame
void AHyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHyCharacter::PlayAttachEffect(FHyActionEffect& InEffect)
{
	if (FXComponent)
	{
		FXComponent->PlayAttachedFX(InEffect, this);
	}
}

void AHyCharacter::StopAttachEffect(FHyActionEffect& InEffect)
{
	if (FXComponent)
	{
		FXComponent->StopFXAttached(InEffect, this);
	}
}

void AHyCharacter::HandleActionExit(EActionHandleExitType ExitType, float BlendOut)
{
	if (!ActionSetComponent)
	{
		ERR_V("Invalid ActionSetCom");
		return;
	}

	switch (ExitType)
	{
	case EActionHandleExitType::EActionExit_Stop:
		ActionSetComponent->ActionStopImmeditaley(BlendOut);
		break;
	case EActionHandleExitType::EActionExit_Free:
		ActionSetComponent->FreeAction();
		break;
	case EActionHandleExitType::EActionExit_Conditional:
		// 조건이 일치하면 STop
		if (ActionSetComponent->IsActionStopCondition())
		{
			HandleActionExit(EActionHandleExitType::EActionExit_Stop, BlendOut);
		}
		break;
	default:
		break;
	}
}

void AHyCharacter::SetPerformingActionPriority(EActionPriority Priority)
{
	if (ActionSetComponent)
	{
		ActionSetComponent->SetPerformingActionPriority(Priority);
	}
}

void AHyCharacter::SetDefaultStoredAction(const bool bForce)
{
	if (ActionSetComponent)
	{
		ActionSetComponent->SetDefaultStoredActionTag(bForce);
	}
}

const bool AHyCharacter::IsDefaultStoredAction() const
{
	// Stored된 Action이 Default Action인지
	if (ActionSetComponent)
	{
		ActionSetComponent->SetDefaultStoredActionTag();
	}
	return false;
}

const bool AHyCharacter::IsEmptyStoredAction() const
{
	if (ActionSetComponent)
	{
		return ActionSetComponent->IsEmptyStoredAction();
	}

	return false;
}

const bool AHyCharacter::IsCanStoreAction(EActionPriority InPriority) const
{
	// Store된 액션 우선순위보다 인자로 넣은 Priority가 더 큰지

	if (ActionSetComponent)
	{
		if (!ActionSetComponent->IsEmptyStoredAction())
		{
			if (ActionSetComponent->StoredPriority >= (int32)InPriority)
			{
				return false;
			}
		}
	}

	return true;
}

FGameplayTag AHyCharacter::GetPerformingActionTag()
{
	// 현재 진행중인 액션 tag 반환
	FGameplayTag PerformingActionTag = FGameplayTag::EmptyTag;

	if (ActionSetComponent)
	{
		PerformingActionTag = ActionSetComponent->GetPerformingActionTag();
	}

	return PerformingActionTag;
}

const FGameplayTag AHyCharacter::GetStoredActionTag()
{
	FGameplayTag StoredTag = FGameplayTag::EmptyTag;
	if (ActionSetComponent)
	{
		StoredTag = ActionSetComponent->GetStoredActionTag();
	}
	return StoredTag;
}

float AHyCharacter::PlayAnimMontage_Custom(UAnimMontage* AnimMontage, float InPlayRate, EMontageBlendType BlendType, FName StartSectionName, float TimeToStartMontageAt)
{
	// 몽타주 시작시 첫 프레임을 지정하기 위해 커스텀
	// TimeToStartMontageAt은 StartSectionName으로 섹션 이동하는 경우에는 사용할 수 없음.

	UAnimInstance* AnimInstance = (GetMesh()) ? GetMesh()->GetAnimInstance() : nullptr;
	if (AnimMontage && AnimInstance)
	{
		switch (BlendType)
		{
		case EMontageBlendType::EMontageBlend_None: // 블렌드 인아웃 모두 안함
			AnimMontage->BlendIn.SetBlendTime(0.0f);
			AnimMontage->BlendOut.SetBlendTime(0.0f);
			break;

		case EMontageBlendType::EMontageBlend_Start: // 블렌드 아웃 안함
			AnimMontage->BlendOut.SetBlendTime(0.0f);
			break;

		case EMontageBlendType::EMontageBlend_End: // 블렌드 인 안함
			AnimMontage->BlendIn.SetBlendTime(0.0f);
			break;

		case EMontageBlendType::EMontageBlend_Both: // 블렌드 인 아웃 모두 함
			break;
		}

		// 애니메이션 몽타주 플레이 속도 Default
		float AnimPlayRate = InPlayRate;
		if (UHyDeveloperSettings* DevSetting = UHyDeveloperSettings::GetDeveloperSettingRef())
		{
			if (DevSetting->IsDefaultAnimPlay())
			{
				AnimPlayRate = 1.0f;
			}
		}

		float const Duration = AnimInstance->Montage_Play(AnimMontage, AnimPlayRate, EMontagePlayReturnType::MontageLength, TimeToStartMontageAt);

		if (Duration > 0.f)
		{
			// Start at a given Section.
			if (StartSectionName != NAME_None)
			{
				AnimInstance->Montage_JumpToSection(StartSectionName, AnimMontage);
			}

			return Duration;
		}
	}

	return 0.f;
}

void AHyCharacter::PauseAction(bool bSetPause)
{
	if (ActionSetComponent)
	{
		ActionSetComponent->PauseAction(bSetPause);
	}
}

void AHyCharacter::SetDesiredPosInfo(const Protocol::hyps_pos_info& InDesiredPosInfoRef)
{
	if (DesiredPosInfo)
	{
		DesiredPosInfo->set_x(InDesiredPosInfoRef.x());
		DesiredPosInfo->set_y(InDesiredPosInfoRef.y());
		DesiredPosInfo->set_z(InDesiredPosInfoRef.z());
		DesiredPosInfo->set_yaw(InDesiredPosInfoRef.yaw());

		DesiredPosInfo->set_move_state(InDesiredPosInfoRef.move_state());

	}
}

void AHyCharacter::SetDesiredPosInfo(const FVector& InPosInfo, const float InYaw, Protocol::hype_move_state InMoveState)
{
	if (DesiredPosInfo)
	{
		DesiredPosInfo->set_x(InPosInfo.X);
		DesiredPosInfo->set_y(InPosInfo.Y);
		DesiredPosInfo->set_z(InPosInfo.Z);
		DesiredPosInfo->set_yaw(InYaw);

		DesiredPosInfo->set_move_state(InMoveState);

	}
}

void AHyCharacter::SetPosInfo(const FVector& InPosInfo, const float InYaw, Protocol::hype_move_state InMoveState)
{
	if (PosInfo)
	{
		PosInfo->set_object_id(ObjectID);
		PosInfo->set_x(InPosInfo.X);
		PosInfo->set_y(InPosInfo.Y);
		PosInfo->set_z(InPosInfo.Z);
		PosInfo->set_yaw(InYaw);
		PosInfo->set_move_state(InMoveState);
	}
}


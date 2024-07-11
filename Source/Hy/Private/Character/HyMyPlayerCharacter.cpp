// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HyMyPlayerCharacter.h"



#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Hy.h"
#include "HyNetworkManager.h"
#include "HySpawnManager.h"



AHyMyPlayerCharacter::AHyMyPlayerCharacter()
{
	DesiredInput = FVector2D::Zero();

}

void AHyMyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;

	if (IntervalTime < ElapsedTime)
	{
		// input이 변경되었을경우에만 cs move 전송
		if (LastDesiredInput != DesiredInput)
		{
			if (GGameInstance->GetManager<UHyNetworkManager>())
			{
				GGameInstance->GetManager<UHyNetworkManager>()->CSMoveObject(PosInfo);
				LastDesiredInput = DesiredInput;
			}

			ElapsedTime = 0.f;
		}

	}
}

void AHyMyPlayerCharacter::AddMappingContext()
{	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerIMC, 0);
		}
	}
}

void AHyMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AddMappingContext();
}

void AHyMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AHyMyPlayerCharacter::Input_Jump);
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Started, this, &AHyMyPlayerCharacter::Input_Equip);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AHyMyPlayerCharacter::Input_Attack);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AHyMyPlayerCharacter::Input_Aim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AHyMyPlayerCharacter::Input_AimOut);

		EnhancedInputComponent->BindAction(SkillAction1, ETriggerEvent::Started, this, &AHyMyPlayerCharacter::Input_Skill1);
		EnhancedInputComponent->BindAction(SkillAction2, ETriggerEvent::Started, this, &AHyMyPlayerCharacter::Input_Skill2);
		EnhancedInputComponent->BindAction(SkillAction3, ETriggerEvent::Started, this, &AHyMyPlayerCharacter::Input_Skill3);

		EnhancedInputComponent->BindAction(TestAction1, ETriggerEvent::Started, this, &AHyMyPlayerCharacter::Input_Test1);
		EnhancedInputComponent->BindAction(TestAction2, ETriggerEvent::Started, this, &AHyMyPlayerCharacter::Input_Test2);
		EnhancedInputComponent->BindAction(TestAction3, ETriggerEvent::Started, this, &AHyMyPlayerCharacter::Input_Test3);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHyMyPlayerCharacter::Input_Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AHyMyPlayerCharacter::Input_Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHyMyPlayerCharacter::Input_Look);
	}
	else
	{
		//UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AHyMyPlayerCharacter::Input_Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (MovementVector.Length() > 0)
	{
		if (Controller != nullptr)
		{
			const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

			// get forward vector
			const FVector FowardMoveVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * MovementVector.Y;

			// get right vector 
			const FVector RightMoveVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * MovementVector.X;
			
			if (PosInfo)
			{
				DesiredMoveDirection = FowardMoveVector + RightMoveVector;
				AddMovementInput(DesiredMoveDirection);
				DesiredInput = FVector2D(DesiredMoveDirection.X, DesiredMoveDirection.Y);
				DesiredYaw = Controller->GetControlRotation().Yaw;

				SetPosInfo(DesiredMoveDirection, DesiredYaw, Protocol::move_state_run);
			}
		}
	}
	else
	{
		// 키 해제
		if (PosInfo)
		{
			DesiredInput = FVector2D::Zero();
			DesiredYaw = 0.0f;
			SetPosInfo(GetActorLocation(), DesiredYaw, Protocol::move_state_idle);
		}
	}
}

void AHyMyPlayerCharacter::Input_Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AHyMyPlayerCharacter::Input_Jump(const FInputActionValue& Value)
{
	ACharacter::Jump();
}

void AHyMyPlayerCharacter::Input_Equip(const FInputActionValue& Value)
{
	GGameInstance->GetManager<UHyNetworkManager>()->CSLeaveGame();
}

void AHyMyPlayerCharacter::Input_Attack(const FInputActionValue& Value)
{
	SCREEN_LOG_V("ObjectID : %lld", ObjectID);
}

void AHyMyPlayerCharacter::Input_Aim(const FInputActionValue& Value)
{

}

void AHyMyPlayerCharacter::Input_AimOut(const FInputActionValue& Value)
{
}

void AHyMyPlayerCharacter::Input_Skill1(const FInputActionValue& Value)
{

}

void AHyMyPlayerCharacter::Input_Skill2(const FInputActionValue& Value)
{
}

void AHyMyPlayerCharacter::Input_Skill3(const FInputActionValue& Value)
{
}

void AHyMyPlayerCharacter::Input_Test1(const FInputActionValue& Value)
{
	EquippedWeaponState = EEquippedWeaponState::UnArmed;
}

void AHyMyPlayerCharacter::Input_Test2(const FInputActionValue& Value)
{
	EquippedWeaponState = EEquippedWeaponState::Rifle;

}

void AHyMyPlayerCharacter::Input_Test3(const FInputActionValue& Value)
{
	EquippedWeaponState = EEquippedWeaponState::Pistol;

}

FString AHyMyPlayerCharacter::GetSocketNumber()
{
	if (UHyNetworkManager* NetworkMgr = GGameInstance->GetManager<UHyNetworkManager>())
	{

		SocketNum = NetworkMgr->GetSocketName();
	}

	return FString();
}

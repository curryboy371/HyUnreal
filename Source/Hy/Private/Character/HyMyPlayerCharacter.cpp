// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HyMyPlayerCharacter.h"



#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


AHyMyPlayerCharacter::AHyMyPlayerCharacter()
{

}

void AHyMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerIMC, 0);
		}
	}
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

	if (Controller != nullptr)
	{
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

		// get forward vector
		const FVector FowardMoveVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * MovementVector.Y;

		// get right vector 
		const FVector RightMoveVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * MovementVector.X;

		AddMovementInput(FowardMoveVector + RightMoveVector);

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
}

void AHyMyPlayerCharacter::Input_Attack(const FInputActionValue& Value)
{
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

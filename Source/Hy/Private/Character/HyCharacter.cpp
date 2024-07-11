// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "HyCharacter.h"
#include "Math/UnrealMathUtility.h"


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


	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
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

// Called every frame
void AHyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DesiredPosInfo)
	{
		// Move
		FVector Direction = FVector(DesiredPosInfo->x(), DesiredPosInfo->y(), DesiredPosInfo->z()) - GetActorLocation();
		if (Direction.Length() > 0.1f)
		{
			Direction.Normalize();
			AddMovementInput(Direction);
		}

		//if (DesiredPosInfo->move_state() == Protocol::hype_move_state::move_state_run)
		//{
		//
		//}

		// Rotation
		FRotator CurrentRotation = GetActorRotation();
		FRotator TargetRotation = CurrentRotation;
		TargetRotation.Yaw = DesiredPosInfo->yaw();

		if (FMath::IsNearlyEqual(TargetRotation.Yaw, GetActorRotation().Yaw, 0.01f) == false)
		{
			FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 10.0f);
			SetActorRotation(NewRotation); 
		}
	}
}

// Called to bind functionality to input
void AHyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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


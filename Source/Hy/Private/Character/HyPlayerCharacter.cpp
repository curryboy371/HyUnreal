// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HyPlayerCharacter.h"
#include "HyPlayerCharacter.h"



#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


AHyPlayerCharacter::AHyPlayerCharacter()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoomCom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoomCom"));
	if (CameraBoomCom)
	{
		CameraBoomCom->SetupAttachment(RootComponent);
		CameraBoomCom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
		CameraBoomCom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	}

	// Create a follow camera
	FollowCameraCom = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCameraCom"));
	if (FollowCameraCom)
	{
		FollowCameraCom->SetupAttachment(CameraBoomCom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
		FollowCameraCom->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	}

}

void AHyPlayerCharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (DesiredPosInfo)
	{
		// Move
		//FVector Direction = FVector(DesiredPosInfo->x(), DesiredPosInfo->y(), DesiredPosInfo->z()) - GetActorLocation();
		//if (Direction.Length() > 0.1f)
		//{
		//	Direction.Normalize();
		//	AddMovementInput(Direction);
		//}
		//
		////if (DesiredPosInfo->move_state() == Protocol::hype_move_state::move_state_run)
		////{
		////
		////}
		//
		//// Rotation
		//FRotator CurrentRotation = GetActorRotation();
		//FRotator TargetRotation = CurrentRotation;
		//TargetRotation.Yaw = DesiredPosInfo->yaw();
		//
		//if (FMath::IsNearlyEqual(TargetRotation.Yaw, GetActorRotation().Yaw, 0.01f) == false)
		//{
		//	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 10.0f);
		//	SetActorRotation(NewRotation);
		//}
	}
}

FString AHyPlayerCharacter::GetPlayerName()
{
	FString strID = FString::Printf(TEXT("%lld"), ObjectID);

	return strID;
}

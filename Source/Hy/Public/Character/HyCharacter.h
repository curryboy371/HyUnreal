// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Hy.h"

#include "HyCharacter.generated.h"

UCLASS()
class HY_API AHyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHyCharacter();
	virtual ~AHyCharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* Get_CameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* Get_FollowCamera() const { return FollowCamera; }


protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveOption, meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterState, FCharacterMoveOption> CharacterMoveOptionMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))

	EEquippedWeaponState EquippedWeaponState;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	ECharacterState CharacterState;

public:
	void SetDesiredPosInfo(const Protocol::hyps_pos_info& InDesiredPosInfoRef);
	void SetDesiredPosInfo(const FVector& InPosInfo, const float InYaw, Protocol::hype_move_state InMoveState);
	void SetPosInfo(const FVector& InPosInfo, const float InYaw, Protocol::hype_move_state InMoveState);

	GETTER(int64, ObjectID)
	SETTER(int64, ObjectID)

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	int64 ObjectID;

	Protocol::hyps_pos_info* PosInfo;
	Protocol::hyps_pos_info* DesiredPosInfo;
};

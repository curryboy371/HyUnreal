// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HyPlayerCharacter.h"
#include "HyMyPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class HY_API AHyMyPlayerCharacter : public AHyPlayerCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AHyMyPlayerCharacter();


protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void Input_Move(const struct FInputActionValue& Value);
	void Input_Look(const struct FInputActionValue& Value);
	void Input_Jump(const struct FInputActionValue& Value);
	void Input_Equip(const struct FInputActionValue& Value);
	void Input_Attack(const struct FInputActionValue& Value);
	void Input_Aim(const struct FInputActionValue& Value);
	void Input_AimOut(const struct FInputActionValue& Value);
	void Input_Skill1(const struct FInputActionValue& Value);
	void Input_Skill2(const struct FInputActionValue& Value);
	void Input_Skill3(const struct FInputActionValue& Value);
	void Input_Test1(const struct FInputActionValue& Value);
	void Input_Test2(const struct FInputActionValue& Value);
	void Input_Test3(const struct FInputActionValue& Value);


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<class UInputMappingContext> PlayerIMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* EquipAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* AimAction;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* SkillAction1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* SkillAction2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* SkillAction3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* TestAction1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* TestAction2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* TestAction3;
};

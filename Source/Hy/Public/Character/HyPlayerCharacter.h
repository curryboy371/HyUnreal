// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HyCharacter.h"
#include "HyPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class HY_API AHyPlayerCharacter : public AHyCharacter
{
	GENERATED_BODY()
public:
	AHyPlayerCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	FString GetPlayerName();


	/** Returns CameraBoom subobject **/
	FORCEINLINE TObjectPtr<class USpringArmComponent> Get_CameraBoom() const { return CameraBoomCom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE TObjectPtr<class UCameraComponent> Get_FollowCamera() const { return FollowCameraCom; }


protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoomCom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCameraCom;
};

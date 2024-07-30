// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HyAnimationTypes.generated.h" // GENERATED_BODY() 매크로를 사용하기 위해 필요	

/**
 * 
 */


UENUM(BlueprintType)
enum class EAnimDirection : uint8
{
	F						UMETA(DisplayName = "Forward Direction"),
	FL						UMETA(DisplayName = "ForwardLeft Direction"),
	FR						UMETA(DisplayName = "ForwardRight Direction"),
	R						UMETA(DisplayName = "Right Direction"),
	L						UMETA(DisplayName = "Left Direction"),
};

UENUM(BlueprintType)
enum class EAnimTurnDirection : uint8
{
	L180				UMETA(DisplayName = "L180 Direction"),
	L90					UMETA(DisplayName = "L90 Direction"),
	R180				UMETA(DisplayName = "R180 Direction"),
	R90					UMETA(DisplayName = "R90 Direction"),
};



USTRUCT(BlueprintType)
struct FDirectionalFowardAnim
{
	GENERATED_BODY()

	FDirectionalFowardAnim()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionalAnim")
	TObjectPtr<class UAnimSequence> F0Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionalAnim")
	TObjectPtr<class UAnimSequence> FL45Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionalAnim")
	TObjectPtr<class UAnimSequence> FR45Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionalAnim")
	TObjectPtr<class UAnimSequence> FL90Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionalAnim")
	TObjectPtr<class UAnimSequence> FR90Anim;
};

USTRUCT(BlueprintType)
struct FDirectionalTurnAnim
{
	GENERATED_BODY()

	FDirectionalTurnAnim()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionalTurnAnim")
	TObjectPtr<class UAnimSequence> L180Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionalTurnAnim")
	TObjectPtr<class UAnimSequence> L90Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionalTurnAnim")
	TObjectPtr<class UAnimSequence> R180Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionalTurnAnim")
	TObjectPtr<class UAnimSequence> R90Anim;

};

USTRUCT(BlueprintType)
struct FDirectionalBackAnim
{
	GENERATED_BODY()

	FDirectionalBackAnim()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionalAnim")
	TObjectPtr<class UAnimSequence> B180Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionalAnim")
	TObjectPtr<class UAnimSequence> BL45Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionalAnim")
	TObjectPtr<class UAnimSequence> BR45Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionalAnim")
	TObjectPtr<class UAnimSequence> BL90Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionalAnim")
	TObjectPtr<class UAnimSequence> BR90Anim;
};


USTRUCT(BlueprintType)
struct FDirectionalAnimSet
{
	GENERATED_BODY()

	FDirectionalAnimSet()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FDirectionalAnimSet")
	FDirectionalFowardAnim Forward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FDirectionalAnimSet")
	FDirectionalBackAnim Backward;
};

USTRUCT(BlueprintType)
struct FCycleAnimSet
{
	GENERATED_BODY()

	FCycleAnimSet()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FAnimSet")
	FDirectionalAnimSet StartAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FAnimSet")
	FDirectionalAnimSet StopAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FAnimSet")
	FDirectionalAnimSet LoopAnims;
};



USTRUCT(BlueprintType)
struct FLocomotionAnims
{
	GENERATED_BODY()

	FLocomotionAnims()
	{

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Directional Anim")
	TObjectPtr<class UAnimSequence> Forward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Directional Anim")
	TObjectPtr<class UAnimSequence> Right;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Directional Anim")
	TObjectPtr<class UAnimSequence> Left;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Directional Anim")
	TObjectPtr<class UAnimSequence> Backward;

};





UENUM(BlueprintType)
enum class ELocomotionDirection : uint8
{
	F_0							UMETA(DisplayName = "F0 F"),
	FL_45						UMETA(DisplayName = "FL45 FL"),
	FR_45						UMETA(DisplayName = "FR45 FR"),
	FL_90						UMETA(DisplayName = "FL90 L"), 
	FR_90						UMETA(DisplayName = "FR90 R"), 
	B_180						UMETA(DisplayName = "B180 B"), 
	BL_45						UMETA(DisplayName = "BL45 BL"), 
	BR_45						UMETA(DisplayName = "BR45 BR"), 
	BL_90						UMETA(DisplayName = "BL90 L"), 
	BR_90						UMETA(DisplayName = "BR90 R"),
};

UENUM(BlueprintType)
enum class ELocomotion4Direction : uint8
{
	F_0							UMETA(DisplayName = "F_0"),
	L_90						UMETA(DisplayName = "L_90"),
	R_90						UMETA(DisplayName = "R_90"),
	B_180						UMETA(DisplayName = "B_180"),
};

USTRUCT(BlueprintType)
struct FDirectionalAnimations
{
	GENERATED_BODY()


	FDirectionalAnimations()
	{
		Forward = nullptr;
		//ForwardRight = nullptr;
		//ForwardLeft = nullptr;
		Right = nullptr;
		Left = nullptr;
		Backward = nullptr;
		//BackwardRight = nullptr;
		//BackwardLeft = nullptr;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Directional Anim")
	TObjectPtr<class UAnimSequence> Forward;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Directional Anim")
	//UAnimSequence* ForwardRight;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Directional Anim")
	//UAnimSequence* ForwardLeft;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Directional Anim")
	TObjectPtr<class UAnimSequence> Right;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Directional Anim")
	TObjectPtr<class UAnimSequence> Left;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Directional Anim")
	TObjectPtr<class UAnimSequence> Backward;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Directional Anim")
	//UAnimSequence* BackwardRight;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Directional Anim")
	//UAnimSequence* BackwardLeft;
};

USTRUCT(BlueprintType)
struct FJumpAnimations
{
	GENERATED_BODY()
	FJumpAnimations()
	{
		JumpStart = nullptr;
		JumpStartLoop = nullptr;
		JumpApex = nullptr;
		JumpFallLand = nullptr;
		JumpFallLoop = nullptr;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Anim")
	TObjectPtr<class UAnimSequence> JumpStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Anim")
	TObjectPtr<class UAnimSequence> JumpStartLoop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Anim")
	TObjectPtr<class UAnimSequence> JumpApex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Anim")
	TObjectPtr<class UAnimSequence> JumpFallLand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Anim")
	TObjectPtr<class UAnimSequence> JumpFallLoop;
};


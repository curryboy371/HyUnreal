// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Engine/World.h" // GetWorld()와 DeltaTime을 위해 필요
#include "UObject/NoExportTypes.h"
#include "DrawDebugHelpers.h"
#include "GameplayTagContainer.h" // FGameplayTag

#include "Game/HyDeveloperSettings.h"
#include "Kismet/GameplayStatics.h"


#include "HyFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Debug")
	static void DrawArrow(UObject* World, const FVector& LineStart, const FVector& LineEnd, float ArrowSize = 30.f, FLinearColor Color = FLinearColor::Green, float Duration = 0.f, float Tickness = 3.f)
	{
		if (World)
		{
			if (const UHyDeveloperSettings* DevSetting = UHyDeveloperSettings::GetDeveloperSetting())
			{
				if (DevSetting->IsDebugDraw())
				{
					UKismetSystemLibrary::DrawDebugArrow(World, LineStart, LineEnd, ArrowSize, Color, Duration, Tickness);
				}
			}

		}
	}

	UFUNCTION(BlueprintCallable, Category = "Debug")
	static void DrawSphere(UWorld* World, const FVector Center, float Radius, int32 Segments = 12, const FLinearColor Color = FLinearColor::Green, float LifeTime = 0.0f, float Thickness = 3.0f)
	{
		if (const UHyDeveloperSettings* DevSetting = UHyDeveloperSettings::GetDeveloperSetting())
		{
			if (DevSetting->IsDebugDraw())
			{
				UKismetSystemLibrary::DrawDebugSphere(World, Center, Radius, Segments, Color, LifeTime, Thickness);
			}
		}
	}
};

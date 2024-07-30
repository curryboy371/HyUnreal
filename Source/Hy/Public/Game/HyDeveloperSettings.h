// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "HyDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig)
class HY_API UHyDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UHyDeveloperSettings();

	static const UHyDeveloperSettings* GetDeveloperSetting();
	static UHyDeveloperSettings* GetDeveloperSettingRef();
	
	
public:
	const bool IsDebugDraw() const { return bDebugDraw; }
	const bool IsEnableBlur() const { return bEnableBlur; }
	const bool IsDefaultAnimPlay() const { return bDefaultAnimPlay; }

	void SetSwitchDebugDraw() { bDebugDraw = !bDebugDraw; }

protected:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "DEBUG | DRAW")
	bool bDebugDraw;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Camera | Blur")
	bool bEnableBlur;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Debug | Animation")
	bool bDefaultAnimPlay;
};

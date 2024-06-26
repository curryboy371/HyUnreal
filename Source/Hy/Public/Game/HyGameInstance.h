// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "HyTypes.h"
#include "HyManagerBase.h"

#include "HyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitGameInstnace();

	UFUNCTION(BlueprintCallable)
	void ClearGameInstnace();

	UFUNCTION(BlueprintCallable)
	void InitManager();

	UFUNCTION(BlueprintCallable)
	void ReleaseManager();

	void UpdateManager(float DeltaTime);

	template<typename T>
	T* GetManager()
	{
		static_assert(TIsDerivedFrom<T, UHyManagerBase>::Value, "T must be derived from UHyManagerBase");
		T* Manager = nullptr;

		for (int32 i = 0; i < Managers.Num(); ++i)
		{
			Manager = Cast<T>(Managers[i]);
			if (Manager)
			{
				break;
			}
		}

		return Manager;
	}

protected:
	UPROPERTY()
	TMap<int32, class UHyManagerBase*> Managers;

};


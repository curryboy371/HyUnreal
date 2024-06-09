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
	/** virtual function to allow custom GameInstances an opportunity to set up what it needs */
	virtual void Init() override;

	/** virtual function to allow custom GameInstances an opportunity to do cleanup when shutting down */
	virtual void Shutdown() override; // Optional: If you need cleanup at the end of the game

	UFUNCTION(BlueprintCallable)
	void InitManager();

	UFUNCTION(BlueprintCallable)
	void ReleaseManager();

	template<typename T>
	T GetManager()
	{
		static_assert(TIsDerivedFrom<T, UHyManagerBase>::Value, "T must be derived from UHyManagerBase");

		EManagerNum FindEnum = T::StaticClass()->GetDefaultObject<T>()->Get_ManagerNum();
		if (Managers.Contains(FindEnum) == true)
		{
			return  Managers[FindEnum];
		}
	}

protected:
	UPROPERTY()
	TMap<EManagerNum, class UHyManagerBase*> Managers;
};


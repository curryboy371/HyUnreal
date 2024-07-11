// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/HyManagerBase.h"

#include "Hy.h"
#include "HySession.h"
#include "HySpawnManager.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHySpawnManager : public UHyManagerBase
{
	GENERATED_BODY()

public:
	UHySpawnManager(const FObjectInitializer& ObjectInitializer)
		:UHyManagerBase(ObjectInitializer)
	{
		Set_ManagerNum(EManagerNum::Spawn);
	}

	// UHyManagerBase을(를) 통해 상속됨
	virtual void InitManager() override;
	virtual void ReleaseManager() override;
	//virtual void UpdateManager(float DeltaTime) override;

	void SpawnMyPlayer(const FObjectSpawnInfo& InObjectInfo);
	void SpawnObject(const FObjectSpawnInfo& InObjectInfo);
	void DeSpawnObject(const int64 ObjectID);
	void MoveObject(const Protocol::hyps_pos_info& InPosInfoRef);

	TObjectPtr<class AHyMyPlayerCharacter> GetMyPlayer() { return MyPlayer; }

protected:
	TMap<int64, TObjectPtr<AActor>> ObjectsMap;

	TObjectPtr<class AHyMyPlayerCharacter> MyPlayer;

};

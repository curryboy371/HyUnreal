// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/HyManagerBase.h"

#include "Hy.h"
#include "HySession.h"
#include "HyNetworkManager.generated.h"

/**
 * 
 */
UCLASS()
class HY_API UHyNetworkManager : public UHyManagerBase
{
	GENERATED_BODY()

public:
	UHyNetworkManager(const FObjectInitializer& ObjectInitializer)
		:UHyManagerBase(ObjectInitializer)
	{
		Set_ManagerNum(EManagerNum::Network);
	}

	// UHyManagerBase을(를) 통해 상속됨
	virtual void InitManager() override;
	virtual void ReleaseManager() override;
	virtual void UpdateManager(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Protocol")
	void CSLogin();

	UFUNCTION(BlueprintCallable, Category = "Protocol")
	void CSLeaveGame();

	void CSMoveObject(Protocol::hyps_pos_info* InDesiredPosInfo);
	
	FString GetSocketName();

private:
	// GameServer
	class FSocket* Socket;
	FString IpAddress = TEXT("127.0.0.1");
	int16 Port = 7777;
	HySessionRef GameSession;
};

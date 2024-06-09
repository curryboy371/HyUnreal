// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HyTypes.h"

/**
 * 
 */
class HY_API HySession : public TSharedFromThis<HySession>
{
public:
	HySession(class FSocket* InSocket);
	~HySession();

	UFUNCTION(BlueprintCallable)
	void HandleRecvPackets();

	void SendPacket(SendBufferRef SendBuffer);

	void Run();

	void Disconnect();

public:
	class FSocket* Socket;

	// 이러면 세션 하나당 스레드 1인데...
	TSharedPtr<class RecvWorker> RecvWorkerThread;
	TSharedPtr<class SendWorker> SendWorkerThread;


	// Networker Thread가 GameThread에 패킷 정보를 전달하기 위한 queue
	TQueue <TArray<uint8>> RecvPacketQueue;

	TQueue<SendBufferRef> SendPacketQueue;

};

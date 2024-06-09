// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Queue.h"
#include "Hy.h"
/**
 * 
 */

class FSocket;

class HY_API RecvWorker : public FRunnable
{
public:
	RecvWorker(FSocket* InSocket, TSharedPtr<class HySession> InSession);
	~RecvWorker();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;

	void Destroy();

private:
	bool ReceivePacket(TArray<uint8>& OutPacket);
	bool ReceiveDesiredBytes(uint8* Results, int32 Size);

protected:
	FRunnableThread* Thread = nullptr;
	bool Running = true;
	FSocket* Socket;
	TWeakPtr<class HySession> SessionRef;
};

class HY_API SendWorker : public FRunnable
{
public:
	SendWorker(FSocket* Socket, TSharedPtr<class HySession> Session);
	~SendWorker();

	// FRunnable을(를) 통해 상속됨
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;

	bool SendPacket(SendBufferRef SendBuffer);

	void Destroy();
private:
	bool SendDesiredBytes(const uint8* Buffer, int32 Size);

protected:
	FRunnableThread* Thread = nullptr;
	bool Running = true;
	FSocket* Socket;
	TWeakPtr<class HySession> SessionRef;
};

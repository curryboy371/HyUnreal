// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/HySession.h"
#include "HyNetworkWorker.h"
#include "Hy.h"

#include "ClientPacketHandler.h"



HySession::HySession(FSocket* InSocket)
	:Socket(InSocket), RecvWorkerThread(nullptr), SendWorkerThread(nullptr), bIsConnect(false)
{

}

HySession::~HySession()
{
	Disconnect();
}

void HySession::HandleRecvPackets()
{
	while (true)
	{
		TArray<uint8> Packet;
		if (RecvPacketQueue.Dequeue(OUT Packet) == false)
		{
			break;
		}

		LOG_V("Packet.Num() : %d", Packet.Num());
		Packet.Num();

		HySessionRef sessionRef = AsShared();
		if (ClientPacketHandler::HandlePacket(sessionRef, Packet.GetData(), Packet.Num()))
		{

		}
		else
		{
			ERR_V("HandlePacket return false");
		}
	}
}

void HySession::SendPacket(SendBufferRef SendBuffer)
{
	SendPacketQueue.Enqueue(SendBuffer);
}

void HySession::Run()
{
	// 세션하나당 스레드를 2개씩 생성?
	RecvWorkerThread = MakeShared<RecvWorker>(Socket, AsShared());
	SendWorkerThread = MakeShared<SendWorker>(Socket, AsShared());
}

void HySession::Disconnect()
{
	LOG_I;
	if (RecvWorkerThread)
	{
		RecvWorkerThread->Destroy();
		RecvWorkerThread = nullptr;
	}

	if (SendWorkerThread)
	{
		SendWorkerThread->Destroy();
		SendWorkerThread = nullptr;
	}
}

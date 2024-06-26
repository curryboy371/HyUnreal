// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/HyNetworkWorker.h"
#include "Sockets.h"
#include "Serialization/ArrayWriter.h"
#include "HySession.h"
#include "SocketSubsystem.h"
RecvWorker::RecvWorker(FSocket* InSocket, TSharedPtr<class HySession> InSession)
	:Socket(InSocket), SessionRef(InSession.ToWeakPtr()), Thread(nullptr)
{
	Thread = FRunnableThread::Create(this, TEXT("RecvWorkerThread"));
}

RecvWorker::~RecvWorker()
{
	if (Thread)
	{
		Thread->WaitForCompletion();
		Thread->Kill();
		delete Thread;
		Thread = nullptr;
	}
}

bool RecvWorker::Init()
{
	LOG_I;
	return true;
}

uint32 RecvWorker::Run()
{
	while (Running)
	{
		TArray<uint8> Packet;

		if (ReceivePacket(OUT Packet))
		{
			if (TSharedPtr<HySession> Session = SessionRef.Pin())
			{
				Session->RecvPacketQueue.Enqueue(Packet);
			}
		}

	}

	return 0;

}

void RecvWorker::Exit()
{
	LOG_I;
}

void RecvWorker::Destroy()
{
	LOG_I;
	Running = false;
}

bool RecvWorker::ReceivePacket(TArray<uint8>& OutPacket)
{
	const int32 HeaderSize = sizeof(FPacketHeader);

	TArray<uint8> HeaderBuffer;

	HeaderBuffer.AddZeroed(HeaderSize);

	if (ReceiveDesiredBytes(HeaderBuffer.GetData(), HeaderSize) == false)
	{
		return false;
	}

	// ID Size
	FPacketHeader Header;

	FMemoryReader Reader(HeaderBuffer);
	Reader << Header;
	LOG_V("Recv PacketID : %d, PacketSize : %d", Header.PacketID, Header.PacketSize);

	OutPacket = HeaderBuffer;

	TArray<uint8> PayloadBuffer;
	const int32 PayloadSize = Header.PacketSize - HeaderSize;
	if (PayloadSize == 0)
	{
		return true;
	}

	OutPacket.AddZeroed(PayloadSize);

	if (ReceiveDesiredBytes(&OutPacket[HeaderSize], PayloadSize))
	{
		return true;
	}

	return false;
}

bool RecvWorker::ReceiveDesiredBytes(uint8* Results, int32 Size)
{
	uint32 PendingDataSize;
	if (Socket->HasPendingData(PendingDataSize) == false || USOCK_Pending <= 0)
	{
		return false;
	}

	int32 Offset = 0;

	while (Size > 0)
	{
		int32 NumRead = 0;
		Socket->Recv(Results + Offset, Size, OUT NumRead);
		check(NumRead <= Size);
		
		if (NumRead <= 0)
		{
			return false;
		}

		Offset += NumRead;
		Size -= NumRead;
	}
	
	return true;
}

SendWorker::SendWorker(FSocket* InSocket, TSharedPtr<class HySession> InSession)
	:Socket(InSocket), SessionRef(InSession.ToWeakPtr()), Thread(nullptr)
{
	Thread = FRunnableThread::Create(this, TEXT("SendWorkerThread"));
}

SendWorker::~SendWorker()
{
	if (Thread)
	{
		Thread->WaitForCompletion();
		Thread->Kill();
		delete Thread;
		Thread = nullptr;
	}
}

bool SendWorker::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("SendWorker::Thread Init"));
	return true;
}

uint32 SendWorker::Run()
{
	while (Running)
	{
		SendBufferRef SendBuffer;

		if (TSharedPtr<HySession> Session = SessionRef.Pin())
		{
			if (Session->SendPacketQueue.Dequeue(OUT SendBuffer))
			{
				if (SendPacket(SendBuffer) == false)
				{
					UE_LOG(LogTemp, Error, TEXT("SendWorker::Run SendPacket error"));
				}
			}
		}

		// Sleep?
	}
	return 0;
}

void SendWorker::Exit()
{
}

bool SendWorker::SendPacket(SendBufferRef SendBuffer)
{
	if (SendDesiredBytes(SendBuffer->Buffer(), SendBuffer->WriteSize()) == false)
		return false;

	return true;
}

void SendWorker::Destroy()
{
	LOG_I;
	Running = false;
}

bool SendWorker::SendDesiredBytes(const uint8* Buffer, int32 Size)
{
	while (Size > 0)
	{

		int32 BytesSent = 0;
		LOG_V("Send Start");

		if (Socket->Send(Buffer, Size, BytesSent) == false)
		{

			ESocketErrors LastError = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLastErrorCode();
			const TCHAR* ErrorText = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetSocketError(LastError);
			ERR_V("Send Error %s", ErrorText);
			return false;
		}

		Size -= BytesSent;
		Buffer += BytesSent;
	}

	return true;
}

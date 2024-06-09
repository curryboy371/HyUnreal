// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/HyNetworkManager.h"
#include "Sockets.h"
#include "Common/TcpSocketBuilder.h"
#include "SocketSubsystem.h"

void UHyNetworkManager::InitManager()
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("Client Socket"));
	FIPv4Address Ip;
	FIPv4Address::Parse(IpAddress, Ip);

	TSharedRef<FInternetAddr> InternetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	InternetAddr->SetIp(Ip.Value);
	InternetAddr->SetPort(Port);

	bool Connected = Socket->Connect(*InternetAddr);

	if (Connected)
	{
		SCREEN_LOG_V("Socket Connect");
		LOG_V("Socket Connect");
		GameSession = MakeShared<HySession>(Socket);
		GameSession->Run();
	}
	else
	{
		SCREEN_ERR_V("Socket Connect");
		ERR_V("Socket Connect");
	}
}

void UHyNetworkManager::ReleaseManager()
{
	LOG_I;

	if (GameSession)
	{
		GameSession->Disconnect();
		GameSession = nullptr;
	}

	// 소켓을 닫고 정리하는 예제 코드
	if (Socket != nullptr)
	{
		// 소켓이 연결 상태일 때 연결을 끊음
		Socket->Close();

		// 소켓을 메모리에서 해제
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
		Socket = nullptr;  // 안전하게 포인터를 null로 설정하여 이후의 접근을 방지
	}

}

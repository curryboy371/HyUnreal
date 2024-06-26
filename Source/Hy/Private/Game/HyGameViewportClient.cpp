#include "Game/HyGameViewportClient.h"

#include "Hy.h"
#include "HyGameInstance.h"

void UHyGameViewportClient::Tick(float DeltaTime)
{
	if (GGameInstance)
	{
		GGameInstance->UpdateManager(DeltaTime);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/HyGameInstance.h"
#include "UObject/UObjectIterator.h"
#include "UObject/Class.h"

#include "HyManagerBase.h"

#include "ClientPacketHandler.h"

void UHyGameInstance::Init()
{
    ClientPacketHandler::Init();
    LOG_I;
    //InitManager();
}

void UHyGameInstance::Shutdown()
{
    LOG_I;
    //ReleaseManager();
}

void UHyGameInstance::InitManager()
{
    LOG_I;
    // 모든 UClass를 순회하며 UManagerBase를 상속하는 클래스를 찾음
    for (TObjectIterator<UClass> It; It; ++It)
    {
        UClass* Class = *It;

        // UManagerBase를 상속하는 클래스인지 확인
        if (Class->IsChildOf(UHyManagerBase::StaticClass()) && !Class->HasAnyClassFlags(CLASS_Abstract))
        {
            // 해당 클래스를 인스턴스화하여 Managers 배열에 추가
            UHyManagerBase* NewManager = NewObject<UHyManagerBase>(this, Class);
            if (NewManager)
            {
                Managers.Add(NewManager->Get_ManagerNum(), NewManager);
            }
        }
    }

    //releaes
    for (auto& manager : Managers)
    {
        manager.Value->InitManager();
    }

}

void UHyGameInstance::ReleaseManager()
{
    LOG_I;

    //releaes
    for (auto manager : Managers)
    {
        if (manager.Value)
        {
            manager.Value->ReleaseManager();

        }
    }

    Managers.Reset();
}

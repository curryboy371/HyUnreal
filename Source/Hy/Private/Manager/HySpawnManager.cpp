// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/HySpawnManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "HyMyPlayerCharacter.h"
#include "HyPlayerController.h"

#include "HyGameModeBase.h"

void UHySpawnManager::InitManager()
{
	ObjectsMap.Reset();
}

void UHySpawnManager::ReleaseManager()
{
    MyPlayer = nullptr;
	ObjectsMap.Reset();
}

void UHySpawnManager::SpawnMyPlayer(const FObjectSpawnInfo& InObjectInfo)
{
    /*
    // Memo
    초기에는 Player가 자동 스폰되지 않고 패킷을 통해 생성하려고 하였음.
    PC와 Player를 직접 생성하고 연결하려고 하였으나 추가적으로 설정해줘야하는 부분들이 있어 ( LocalPlayer등..)
    그냥 언리얼에서 직접 생성한 PC를 사용하는게 나을 것 같아 수정함
    */

    FString PlayerBlueprintPath = TEXT("/Game/Blueprints/Character/HyMyPlayer_BP.HyMyPlayer_BP_C");
    UClass* PlayerBPClass = StaticLoadClass(AActor::StaticClass(), nullptr, *PlayerBlueprintPath);

    if (PlayerBPClass)
    {
        // PC 먼저 생성
        APlayerController* PC = nullptr;
        AGameModeBase* MyGameMode = Cast<AGameModeBase>(UGameplayStatics::GetGameMode(this));
        if (MyGameMode)
        {
            FString Option;
            PC = MyGameMode->SpawnPlayerController(ROLE_AutonomousProxy, Option);
        }

        if (PC)
        {
            AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(PlayerBPClass, InObjectInfo.Location, InObjectInfo.Rotation);
            if (SpawnedActor)
            {
                if (AActor* Actor = Cast<AActor>(SpawnedActor))
                {
                    // NewCharacter Init
                    ObjectsMap.Emplace(InObjectInfo.ObjectID, Actor);
                    MyPlayer = Cast<AHyMyPlayerCharacter>(SpawnedActor);
                    if (MyPlayer)
                    {
                        PC->Possess(MyPlayer);
                        MyPlayer->AddMappingContext();
                        MyPlayer->Set_ObjectID(InObjectInfo.ObjectID);

                    }
                }
            }
            else
            {
                ERR_V("Character Create Fail ID : %lld", InObjectInfo.ObjectID);
                return;
            }

        }


    }
    else
    {
        ERR_V("Character Class find error %lld", InObjectInfo.ObjectID);
        return;
    }
}

void UHySpawnManager::SpawnObject(const FObjectSpawnInfo& InObjectInfo)
{
    FString BlueprintPath = TEXT("/Game/Blueprints/Character/HyOtherPlayer_BP.HyOtherPlayer_BP_C");
    UClass* PlayerBPClass = StaticLoadClass(AActor::StaticClass(), nullptr, *BlueprintPath);

    if (PlayerBPClass)
    {
        AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(PlayerBPClass, InObjectInfo.Location, InObjectInfo.Rotation);

        if (SpawnedActor)
        {
            if (AActor* Actor = Cast<AActor>(SpawnedActor))
            {

                // NewCharacter Init
                ObjectsMap.Emplace(InObjectInfo.ObjectID, Actor);

                AHyPlayerCharacter* HyPlayer = Cast<AHyPlayerCharacter>(SpawnedActor);
                if (HyPlayer)
                {
                    HyPlayer->Set_ObjectID(InObjectInfo.ObjectID);
                }
            }
        }
        else
        {
            ERR_V("Character Create Fail ID : %lld", InObjectInfo.ObjectID);
            return;
        }
    }
    else
    {
        ERR_V("Character Class find error %lld", InObjectInfo.ObjectID);
        return;
    }
}

void UHySpawnManager::DeSpawnObject(const int64 ObjectID)
{
    TObjectPtr<AActor>* Object = ObjectsMap.Find(ObjectID);
    if (Object == nullptr || *Object == nullptr)
    {
        ERR_V("invaild object id %lld", ObjectID);
        return;
    }
    
    (*Object)->Destroy();
    ObjectsMap.Remove(ObjectID);
}

void UHySpawnManager::MoveObject(const int64 ObjectID, const FVector& InLocation)
{
    TObjectPtr<AActor>* Object = ObjectsMap.Find(ObjectID);
    if (Object == nullptr || *Object == nullptr)
    {
        ERR_V("invaild object id %lld", ObjectID);
        return;
    }
    
    (*Object)->SetActorLocation(InLocation);

}

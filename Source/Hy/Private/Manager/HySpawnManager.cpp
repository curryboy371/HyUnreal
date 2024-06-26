// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/HySpawnManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "HyMyPlayerCharacter.h"

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
    FString BlueprintPath = TEXT("/Game/Blueprints/Character/HyMyPlayer_BP.HyMyPlayer_BP_C");
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
                MyPlayer = Cast<AHyMyPlayerCharacter>(SpawnedActor);
                if (MyPlayer)
                {
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

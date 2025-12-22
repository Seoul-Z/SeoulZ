// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/SZMonsterSpawner.h"
#include "Utils/SpawnUtils.h"
#include "Interface/SZPoolableInterface.h"
#include "GameMode/SZPoolManager.h" 

ASZMonsterSpawner::ASZMonsterSpawner()
{
}

void ASZMonsterSpawner::SpawnMonster(class USZPoolManager* PoolManager)
{
    if (!PoolManager || !MonsterClass) return;

    FVector SpawnLocation;
    bool bFound = false;

    for (int32 i = 0; i < MaxRetries; i++)
    {
        if (!SpawnUtil::GetRandomSpawnLocation(GetWorld(), GetActorLocation(), SpawnRadius, SpawnLocation))
        {
            continue;
        }
  
        if (SpawnUtil::IsLocationFree(GetWorld(), SpawnLocation))
        {
            bFound = true;
            break;
        }
    }

    if (!bFound)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to find valid spawn location"));
        return;
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Success to find valid spawn location"));
    }

    FTransform SpawnTransform;
    SpawnTransform.SetLocation(SpawnLocation);

    AActor* Actor = PoolManager->GetActor(MonsterClass, SpawnTransform);


    UE_LOG(LogTemp, Log, TEXT("Actor: %s"), *GetNameSafe(Actor));

    UE_LOG(LogTemp, Log, TEXT("Class Implements Interface: %d"),
        Actor->GetClass()->ImplementsInterface(USZPoolableInterface::StaticClass()) ? 1 : 0);

    if (Actor && Actor->GetClass()->ImplementsInterface(USZPoolableInterface::StaticClass()))
    {
        UE_LOG(LogTemp, Log, TEXT("Spawn Ok!"));
        ISZPoolableInterface::Execute_OnSpawnFromPool(Actor);

    }
}

void ASZMonsterSpawner::SpawnAll(USZPoolManager* PoolManager)
{
    for (int32 i = 0; i < SpawnCount; i++)
    {
           SpawnMonster(PoolManager);
    }
}


//void ASZMonsterSpawner::SpawnAll()
//{
//    for (int32 i = 0; i < SpawnCount; i++)
//    {
//        SpawnMonster();
//    }
//}

// Called when the game starts or when spawned
void ASZMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
}



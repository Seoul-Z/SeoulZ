// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SZGameModeBase.h"
#include "SZGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/SZPoolManager.h"

void ASZGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    PoolManager = GetGameInstance()->GetSubsystem<USZPoolManager>();

    // 스포너를 담을 배열. 특정 클래스가 들어가지 않기 때문에 Actor로 선언.
    TArray<AActor*> FoundActors;

    // 
    UGameplayStatics::GetAllActorsOfClass(
        GetWorld(),
        ASZMonsterSpawner::StaticClass(),
        FoundActors
    );

    // 캐스팅해서 Spawners에 저장
    Spawners.Empty();

    for (AActor* Actor : FoundActors)
    {
        if (ASZMonsterSpawner* Spawner = Cast<ASZMonsterSpawner>(Actor))
        {
            Spawners.Add(Spawner);
        }
    }
    SpawnStageMonsters();
}

void ASZGameModeBase::SpawnStageMonsters()
{
    AliveMonsterCount = 0;

    for (ASZMonsterSpawner* Spawner : Spawners)
    {
        if (!Spawner) continue;
 
        Spawner->SpawnAll(PoolManager);
        AliveMonsterCount += Spawner->GetSpawnCount();
    }

    UE_LOG(LogTemp, Log,
        TEXT("Stage Start - Alive Monsters: %d"),
        AliveMonsterCount);
}

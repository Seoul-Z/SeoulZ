// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SZMonsterSpawner.generated.h"

UCLASS()
class PROJECTSEOULZ_API ASZMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASZMonsterSpawner();

	void SpawnMonster(class USZPoolManager* PoolManager);

	void SpawnAll(class USZPoolManager* PoolManager);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	FORCEINLINE int32 GetSpawnCount() { return SpawnCount; }

protected:
	// 스폰 범위 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRadius = 1000.f;

	// 장애물 존재 등으로 스폰의 실패 했을 경우, 최대 시도 횟수.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxRetries = 5;

	// 스폰할 몬스터를 담는 변수.
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "MonsterClass")
	TSubclassOf<AActor> MonsterClass;

	// 스폰할 몬스터의 수
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SpawnCount = 4;


};

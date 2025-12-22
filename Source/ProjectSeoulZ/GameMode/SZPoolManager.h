// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SZPoolManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSEOULZ_API USZPoolManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Pooling(TSubclassOf<AActor> ActorClass, int32 Count);

	AActor* GetActor(TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform);

	// 풀에 액터 반환
	void ReturnActor(AActor* Actor);

	// 스테이지 종료 시 불필요한 풀 정리
	void CleanupForNextStage(const TArray<TSubclassOf<AActor>>& StageActorList);

private:
	TMap<TSubclassOf<AActor>, TArray<AActor*>> PoolMap;

	AActor* CreateNewActor(TSubclassOf<AActor> ActorClass);
	
};

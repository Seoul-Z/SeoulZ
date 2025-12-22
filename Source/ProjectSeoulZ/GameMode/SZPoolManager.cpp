// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SZPoolManager.h"
#include "SZPoolManager.h"
#include "Interface/SZPoolableInterface.h"

void USZPoolManager::Pooling(TSubclassOf<AActor> ActorClass, int32 Count)
{
	TArray<AActor*>& Pool = PoolMap.FindOrAdd(ActorClass);

	UWorld* World = GetWorld();
	if (!World) return;

	for (int32 i = 0; i < Count; i++)
	{
		AActor* NewActor = CreateNewActor(ActorClass);
		Pool.Add(NewActor);
	}


}

AActor* USZPoolManager::GetActor(TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform)
{
	TArray<AActor*>& Pool = PoolMap.FindOrAdd(ActorClass);

	for (AActor* Actor : Pool)
	{
		if (Actor && Actor->IsHidden()) // 비활성 상태 확인
		{
			Actor->SetActorTransform(SpawnTransform);
			ISZPoolableInterface::Execute_OnSpawnFromPool(Actor);
			return Actor;
		}
	}

	// 부족하면 새로 생성
	AActor* NewActor = CreateNewActor(ActorClass);
	if (NewActor)
	{
		Pool.Add(NewActor);
		NewActor->SetActorTransform(SpawnTransform);
		ISZPoolableInterface::Execute_OnSpawnFromPool(NewActor);
	}

	return NewActor;
}

void USZPoolManager::ReturnActor(AActor* Actor)
{
	if (!Actor || !Actor->GetClass()->ImplementsInterface(USZPoolableInterface::StaticClass())) return;

	ISZPoolableInterface::Execute_OnReturnToPool(Actor);
}

void USZPoolManager::CleanupForNextStage(const TArray<TSubclassOf<AActor>>& StageActorList)
{
	for (auto It = PoolMap.CreateIterator(); It; ++It)
	{
		if (!StageActorList.Contains(It.Key()))
		{
			for (AActor* Actor : It.Value())
			{
				if (Actor) Actor->Destroy();
			}
			It.RemoveCurrent();
		}
	}
}

AActor* USZPoolManager::CreateNewActor(TSubclassOf<AActor> ActorClass)
{
	UWorld* World = GetWorld();
	if (!World || !*ActorClass) return nullptr;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* NewActor = World->SpawnActor<AActor>(ActorClass, FTransform::Identity, Params);

	if (NewActor && NewActor->GetClass()->ImplementsInterface(USZPoolableInterface::StaticClass()))
	{
		ISZPoolableInterface::Execute_OnReturnToPool(NewActor);
	}

	return NewActor;
}

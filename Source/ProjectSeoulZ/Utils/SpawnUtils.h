// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

class SpawnUtil
{
public:
    // NavMesh 기준 랜덤 위치 가져오기
    static bool GetRandomSpawnLocation(UWorld* World, const FVector& Origin, float Radius, FVector& OutLocation)
    {
        // World가 존재하지 않으면 종료
        if (!World) return false;

        // 현재 월드에서 사용되는 네비게이션 시스템 객체를 가져오고 그것이 nullptr이면 종료
        UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(World);
        if (!NavSys) return false;
        
        // NavMesh 상에서 랜덤한 위치를 얻음.
        FNavLocation NavLoc;
        if (NavSys->GetRandomReachablePointInRadius(Origin, Radius, NavLoc))
        {
            OutLocation = NavLoc.Location;
            return true;
        }

        return false;
    }

    // 충돌 체크
    static bool IsLocationFree(UWorld* World, const FVector& Location, float Radius = 50.f, float HalfHeight = 88.f)
    {
        // World가 존재하지 않으면 종료
        if (!World) return false;

        
        // 충돌하는 것이 있으면 
        FHitResult Hit;
        return World->SweepSingleByChannel(
            Hit,
            Location,
            Location,
            FQuat::Identity,
            ECC_Pawn,
            FCollisionShape::MakeCapsule(Radius, HalfHeight)
        );
    }
};
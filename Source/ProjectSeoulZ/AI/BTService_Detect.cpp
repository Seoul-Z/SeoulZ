// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Detect.h"
#include "SZAI.h"
#include "AIController.h"
#include "Interface/SZNormalAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Physics/SZCollision.h"
#include "Engine/OverlapResult.h"

UBTService_Detect::UBTService_Detect()
{
	// 비헤이비어 트리에서의 노드 이름.
	NodeName = TEXT("Detect");

	// Tick의 진행 간격
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Owner의 폰이 존재하는지 검사
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return;
	}

	// 폰의 위치
	FVector Center = ControllingPawn->GetActorLocation();
	// 폰이 속한 월드
	UWorld* World = ControllingPawn->GetWorld();
	
	// 월드가 존재하는지 검사
	if (World == nullptr)
	{
		return;
	}

	// 몬스터의 데이터를 반환하는 인터페이스가 있는지 검사
	ISZNormalAIInterface* AIPawn = Cast<ISZNormalAIInterface>(ControllingPawn);
	if (AIPawn == nullptr)
	{
		return;
	}

	// 플레이어 감지 범위 
	float DetectRadius = AIPawn->GetAIDetectRange();

	// 
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		CCHANNEL_SZACTION,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	// 충돌 결과들 중 플레이어를 찾아 블랙보드의 변수에 할당.
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());

			// 검사 거리 늘리는 로직 나중에 실행
			if (Pawn && Pawn->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Pawn);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				
				DrawDebugPoint(World, Pawn->GetActorLocation(), 10.0f , FColor::Green, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), Pawn->GetActorLocation(), FColor::Green, false, 0.2f);
				return;
			}
		}	
	}

	// 플레이어를 찾지 못했다면 BBKEY_TARGET에 nullptr 할당
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}



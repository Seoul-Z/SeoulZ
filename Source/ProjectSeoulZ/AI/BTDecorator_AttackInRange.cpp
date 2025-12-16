// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_AttackInRange.h"
#include "BTDecorator_AttackInRange.h"
#include "SZAI.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/SZNormalAIInterface.h"

UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// Super 호출
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	// 폰의 존재 여부 확인
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return false;
	}

	// 몬스터의 데이터를 반환하는 인터페이스를 구현했는지 여부 확인.
	ISZNormalAIInterface* AIPawn = Cast<ISZNormalAIInterface>(ControllingPawn);
	if (AIPawn == nullptr)
	{
		return false;
	}

	// 타겟이 설정되어 있는지 확인.
	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (Target == nullptr)
	{
		return false;
	}

	// 타겟까지의 거리를 구함.
	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
	// 몬스터의 공격가능 범위를 가져옴.
	float AttackRangeWithRadius = AIPawn->GetAIAttackRange();
	// 타겟까지의 거리가 몬스터의 공격가능 범위이면 true를 반환.
	bResult = (DistanceToTarget <= AttackRangeWithRadius);

	return bResult;
}

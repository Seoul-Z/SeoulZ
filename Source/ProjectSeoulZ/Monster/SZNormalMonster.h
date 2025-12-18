// Fill out your copyright notice in the Description page of Project Settings.

//﻿---------------------------------------------------------------------------------------------------------
// Author       : 이혜성
// Date       : 2025-12-14
// Copyright   : 회사 또는 팀 이름
//
// Description : 페이즈 1에서 사용할 몬스터의 클래스.
//               SZCharacterBase를 상속받아 사용하고 메시와 애니메이션 블루프린트를 바꿔서 사용함.
//               
//                 
//----------------------------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Character/SZCharacterBase.h"
#include "Interface/SZNormalAIInterface.h"
#include "SZNormalMonsterAttackData.h"
#include "Interface/SZMonsterAttackInterface.h"
#include "SZNormalMonster.generated.h"


UCLASS()
class PROJECTSEOULZ_API ASZNormalMonster : public ASZCharacterBase, public ISZNormalAIInterface, public ISZMonsterAttackInterface
{
	GENERATED_BODY()
	
public:
	ASZNormalMonster();

	FORCEINLINE UBTTask_Attack* GetAttackTask(){ return CurrentAttackTask; }

	FORCEINLINE void SetCurrentAttackAbility(class UGameplayAbility* Ability) { CurrentAttackAbility = Ability; }

// AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI(class UBTTask_Attack* Task) override;

	FAICharacterAttackFinished OnAttackFinished;

	virtual UAnimMontage* GetAttackAnimMontage() override;
	virtual int GetSectionCount() override;

	// ASC 초기화를 위해 사용.
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY()
	UBTTask_Attack* CurrentAttackTask;


// Attack Section
protected:

	FORCEINLINE void ClearCurrentAttackAblility() { CurrentAttackAbility = nullptr; }

	virtual void OnAttackHitNotify() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Attack")
	TObjectPtr<class USZNormalMonsterAttackData> AttackDataAsset;

	UPROPERTY()
	class UGameplayAbility* CurrentAttackAbility;

	
	
};

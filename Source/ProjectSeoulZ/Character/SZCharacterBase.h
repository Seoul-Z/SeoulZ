// Fill out your copyright notice in the Description page of Project Settings.
//---------------------------------------------------------------------------------------------------------
// Author       : 이혜성
// Date       : 2025-12-11
// Copyright   : ???
//
// Description : CharacterBase 클래스 
//               플레이어와 몬스터가 상속받아 사용할 클래스. 
//				 플레이어와 몬스터가 공통으로 사용하는 메시 컴포넌트, 캡슐 컴포넌트, ASC등의 변수가 있다.
//                 
//----------------------------------------------------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "SZCharacterBase.generated.h"


UCLASS()
class PROJECTSEOULZ_API ASZCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASZCharacterBase();

	// GAS 시스템을 가져오는 함수.
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;


protected:
	// 죽음 상태를 설정하는 함수.
	virtual void SetDead();

protected:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<class USZAttributeSet> AttributeSet;

};

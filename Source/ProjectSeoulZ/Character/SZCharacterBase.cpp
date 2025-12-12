// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SZCharacterBase.h"

// Sets default values
ASZCharacterBase::ASZCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// 메시 컴포넌트 콜리전 끄기
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	// ASC 초기화. 플레이어는 State에서 초기화(멀티의 경우)
	ASC = nullptr;
}

// GAS를 위한 ASC 가져오기
UAbilitySystemComponent* ASZCharacterBase::GetAbilitySystemComponent() const
{
	return ASC;
}


// 죽었을 때 호출하는 함수. 플레이어의 경우에는 로비로 되돌아가고 몬스터의 경우에는 죽는 애니메이션을 재생하고 콜리전 등을 끈다.
void ASZCharacterBase::SetDead()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->StopAllMontages(0.0f);


	}
}




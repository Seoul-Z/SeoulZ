// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SZGA_AttackHitCheck.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSEOULZ_API USZGA_AttackHitCheck : public UGameplayAbility
{
	GENERATED_BODY()

public:
	USZGA_AttackHitCheck();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SZAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class PROJECTSEOULZ_API USZAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	USZAttributeSet();

	ATTRIBUTE_ACCESSORS(USZAttributeSet, AttackRange);
	ATTRIBUTE_ACCESSORS(USZAttributeSet, MaxAttackRange);
	ATTRIBUTE_ACCESSORS(USZAttributeSet, AttackRadius);
	ATTRIBUTE_ACCESSORS(USZAttributeSet, MaxAttackRadius);
	ATTRIBUTE_ACCESSORS(USZAttributeSet, AttackRate);
	ATTRIBUTE_ACCESSORS(USZAttributeSet, MaxAttackRate);
	ATTRIBUTE_ACCESSORS(USZAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(USZAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(USZAttributeSet, AttackDamage);
	ATTRIBUTE_ACCESSORS(USZAttributeSet, MaxAttackDamage);



	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;


protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta=(AllowPrivateAccess = true))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Attack",meta=(AllowPrivateAccess = true))
	FGameplayAttributeData AttackDamage;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackDamage;

};

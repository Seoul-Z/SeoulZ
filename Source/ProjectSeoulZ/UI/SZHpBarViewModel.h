// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "Attribute/SZAttributeSet.h"
#include "SZHpBarViewModel.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSEOULZ_API USZHpBarViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void Initialize(UAbilitySystemComponent* InASC);

protected:
    UPROPERTY(BlueprintReadOnly, FieldNotify, Category = "Health")
    float Health = 0.f;

    UPROPERTY(BlueprintReadOnly, FieldNotify, Category = "Health")
    float MaxHealth = 1.f;

    UPROPERTY(BlueprintReadOnly, FieldNotify, Category = "Health")
    float HealthPercent = 1.f;

private:
    void Bind();
    void Unbind();

    void OnHealthChanged(const FOnAttributeChangeData& Data);
    void OnMaxHealthChanged(const FOnAttributeChangeData& Data);

private:
    TWeakObjectPtr<UAbilitySystemComponent> ASC;
    const USZAttributeSet* AttributeSet;

    FDelegateHandle HealthChangedHandle;
    FDelegateHandle MaxHealthChangedHandle;
	
};

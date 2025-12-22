// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SZHpBarViewModel.h"
#include "AbilitySystemComponent.h"
#include "Attribute/SZAttributeSet.h"
#include "MVVMViewModelBase.h"

void USZHpBarViewModel::Initialize(UAbilitySystemComponent* InASC)
{
    ASC = InASC;
    if (!ASC.IsValid()) return;

    AttributeSet = ASC->GetSet<USZAttributeSet>();
    if (!AttributeSet) return;

    UE_MVVM_SET_PROPERTY_VALUE(Health, AttributeSet->GetHealth());
    UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, AttributeSet->GetMaxHealth());
    UE_MVVM_SET_PROPERTY_VALUE(
        HealthPercent,
        AttributeSet->GetHealth() / AttributeSet->GetMaxHealth());

    Bind();
}

void USZHpBarViewModel::Bind()
{
    HealthChangedHandle =
        ASC->GetGameplayAttributeValueChangeDelegate(
            USZAttributeSet::GetHealthAttribute())
        .AddUObject(this, &USZHpBarViewModel::OnHealthChanged);

    MaxHealthChangedHandle =
        ASC->GetGameplayAttributeValueChangeDelegate(
            USZAttributeSet::GetMaxHealthAttribute())
        .AddUObject(this, &USZHpBarViewModel::OnMaxHealthChanged);
}

void USZHpBarViewModel::OnHealthChanged(const FOnAttributeChangeData& Data)
{
    UE_MVVM_SET_PROPERTY_VALUE(Health, Data.NewValue);
    UE_MVVM_SET_PROPERTY_VALUE(
        HealthPercent,
        Data.NewValue / MaxHealth);
}   

void USZHpBarViewModel::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
    UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, Data.NewValue);
    UE_MVVM_SET_PROPERTY_VALUE(
        HealthPercent,
        Health / Data.NewValue);
}

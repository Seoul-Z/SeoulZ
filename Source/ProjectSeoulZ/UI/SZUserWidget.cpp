// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SZUserWidget.h"
#include "AbilitySystemBlueprintLibrary.h"

void USZUserWidget::SetAbilitySystemComponent(AActor* InOwner)
{
    if (IsValid(InOwner))
    {
        ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InOwner);
    }
}

UAbilitySystemComponent* USZUserWidget::GetAbilitySystemComponent() const
{
    return ASC;
}

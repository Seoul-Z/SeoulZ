// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SZHpBarUserWidget.h"
#include "AbilitySystemComponent.h"
#include "Attribute/SZAttributeSet.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "SZHpBarViewModel.h"


void USZHpBarUserWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	Super::SetAbilitySystemComponent(InOwner);

	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(USZAttributeSet::GetHealthAttribute()).AddUObject(this, &USZHpBarUserWidget::OnHealthChanged);
		ASC->GetGameplayAttributeValueChangeDelegate(USZAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &USZHpBarUserWidget::OnMaxHealthChanged);

		const USZAttributeSet* CurrentAttributeSet = ASC->GetSet<USZAttributeSet>();
		if (CurrentAttributeSet)
		{
			CurrentHealth = CurrentAttributeSet->GetHealth();
			CurrentMaxHealth = CurrentAttributeSet->GetMaxHealth();

			if (CurrentMaxHealth > 0.0f)
			{
				UpdateHpBar();
			}
		}
		
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AttributeSet ASC is nullptr"));
	}
}

void USZHpBarUserWidget::OnHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	CurrentHealth = ChangeData.NewValue;
	UpdateHpBar();
}

void USZHpBarUserWidget::OnMaxHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	CurrentMaxHealth = ChangeData.NewValue;
	UpdateHpBar();
}

void USZHpBarUserWidget::UpdateHpBar()
{
	if (PbHpBar)
	{
		PbHpBar->SetPercent(CurrentHealth / CurrentMaxHealth);
	}

	if (TxtHpStat)
	{
		TxtHpStat->SetText(FText::FromString(FString::Printf(TEXT("%.0f/%.0f"), CurrentHealth, CurrentMaxHealth)));
	}
}



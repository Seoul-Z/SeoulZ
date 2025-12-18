// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SZUserWidget.h"
#include "SZHpBarUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSEOULZ_API USZHpBarUserWidget : public USZUserWidget
{
	GENERATED_BODY()
	
protected:

protected:
	float CurrentHealth;
	float CurrentMaxHealth = 0.1f;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SZNormalMonsterAttackData.generated.h"

USTRUCT(BlueprintType)
struct FMonsterAttackData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int SectionCount;
};

/**
 * 
 */
UCLASS()
class PROJECTSEOULZ_API USZNormalMonsterAttackData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FMonsterAttackData AttackData;
};

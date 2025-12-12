// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SZNormalAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSEOULZ_API ASZNormalAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASZNormalAIController();

	void RunAI();
	void StopAI();

	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;
};

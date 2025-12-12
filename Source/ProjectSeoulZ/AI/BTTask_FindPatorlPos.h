// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPatorlPos.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSEOULZ_API UBTTask_FindPatorlPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindPatorlPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};

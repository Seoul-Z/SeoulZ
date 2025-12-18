// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SZInteractionInterface.generated.h"

//---------------------------------------------------------------------------------------------------------
// Author       : 고미소
// Date         : 2025-12-17
// Copyright    : Coding Dead
//
// Description  : Interaction 인터페이스
//               아이템 상호작용 인터페이스로, Item Base 및 Item Data Component에서 상속받음.
//      
//               - OnInteractWith : 아이템과 상호작용 발생 시 호출
//               - OnLookAt       : 아이템을 볼 때 표시할 아이템 설명 정보 반환          
//----------------------------------------------------------------------------------------------------------

UINTERFACE(MinimalAPI)
class USZInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECTSEOULZ_API ISZInteractionInterface
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void OnInteractWith(AActor* Interactor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	FText OnLookAt() const;
};

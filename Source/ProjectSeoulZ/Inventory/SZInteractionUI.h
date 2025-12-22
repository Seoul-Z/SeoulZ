// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SZInteractionUI.generated.h"

//---------------------------------------------------------------------------------------------------------
// Author       : 고미소
// Date         : 2025-12-17
// Copyright    : Coding Dead
//
// Description  : Interaction 사용자 위젯
//               아이템 정보를 띄우는 UI 제어로, Interaction Component에서 이를 사용.
//           
//----------------------------------------------------------------------------------------------------------

class UTextBlock;

UCLASS()
class PROJECTSEOULZ_API USZInteractionUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetMessage(const FText& InText);

protected:
	// BP에 있는 TextBlock 이름과 동일해야 자동 바인딩됨
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Txt_Interact;

private:
	FText Message;
};

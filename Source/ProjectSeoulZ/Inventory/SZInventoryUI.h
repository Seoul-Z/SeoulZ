// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/Components/SZInventoryComponent.h"
#include "SZInventoryUI.generated.h"

//---------------------------------------------------------------------------------------------------------
// Author       : 고미소
// Date         : 2025-12-22
// Copyright    : 
//
// Description  : Inventory 사용자 위젯
//               슬롯 관리
//                 
//----------------------------------------------------------------------------------------------------------

class USZInventorySlot;
class UWrapBox;

/**
 * 
 */
UCLASS()
class PROJECTSEOULZ_API USZInventoryUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void RefreshInventory(USZInventoryComponent* InSZInventory);

	UFUNCTION(BlueprintCallable)
	void CreateInventorySlots();

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USZInventorySlot> InventorySlotClass;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWrapBox> WrapBox_Inventory;

private:
	TObjectPtr<USZInventoryComponent> SZInventory;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/SZItemTemplete.h"
#include "SZInventoryComponent.generated.h"

//---------------------------------------------------------------------------------------------------------
// Author       : 고미소
// Date         : 2025-12-17
// Copyright    : Coding Dead
//
// Description  : 인벤토리 컴포넌트
//               
//             
//----------------------------------------------------------------------------------------------------------

USTRUCT(BlueprintType)
struct FItemSlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ItemId = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StackCount = 0; 
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSEOULZ_API USZInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USZInventoryComponent();

	// 데이터 테이블
	const TObjectPtr<FItemTemplete> GetItemData(int32 ItemID) const;
	// 슬롯
	int32 FindMatchingSlot(int32 ItemID) const;
	int32 FindEmptySlot() const;              
	void AddToSlot(int32 Index, int32 ItemCount);
	void AddToNewSlot(uint8 ItemID, int32 ItemCount, int32 Index);
	// 사운드
	void PlayItemSFX(USoundBase* Sound) const;
	USoundBase* GetItemSFX(int32 ItemID) const;
	// 아이템 줍기
	int32 PickUp(int32 ItemID, int32 ItemCount);

	UFUNCTION(BlueprintCallable)
	void PrintInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FDataTableRowHandle ItemDataHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory | Data")
	TObjectPtr<UDataTable> DT_ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory | Inventory Count")
	int32 InventorySize = 13; // 인벤토리에서 관리하는 아이템 총 개수

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FItemSlot> ItemSlots;
};

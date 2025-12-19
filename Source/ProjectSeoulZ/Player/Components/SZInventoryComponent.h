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
//           인벤토리 슬롯 구조체 및 인벤토리 기능 구현    
//             
//----------------------------------------------------------------------------------------------------------

USTRUCT(BlueprintType)
struct FItemSlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

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

#pragma region 아이템 줍기
	// 데이터 테이블
	const FItemTemplete* GetItemData(FName ItemID) const;
	// 슬롯
	int32 FindMatchingSlot(FName ItemID) const;
	int32 FindEmptySlot() const;
	void AddToSlot(FName ItemID, int32 Index, int32 ItemCount);
	void AddToNewSlot(FName ItemID, int32 ItemCount, int32 Index);
	// 사운드
	void PlayItemSFX(USoundBase* Sound) const;
	USoundBase* GetItemSFX(FName ItemID) const;
	// 아이템 줍기
	int32 PickUp(FName ItemID, int32 ItemCount);
#pragma endregion

	UFUNCTION(BlueprintCallable)
	void PrintInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory | Data")
	TObjectPtr<UDataTable> ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory | Inventory Count")
	int32 MaxSlotCount = 14;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FItemSlot> ItemSlots;
};

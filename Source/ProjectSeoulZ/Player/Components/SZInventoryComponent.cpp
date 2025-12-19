// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/SZInventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values for this component's properties
USZInventoryComponent::USZInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

const TObjectPtr<FItemTemplete> USZInventoryComponent::GetItemData(int32 ItemID) const
{
	if (DT_ItemData)
	{
		const FName RowName(*FString::FromInt(ItemID));
		return DT_ItemData->FindRow<FItemTemplete>(RowName, TEXT("GetItemData"));
	}
}

int32 USZInventoryComponent::FindMatchingSlot(int32 ItemID) const
{
	const TObjectPtr<FItemTemplete> Info = GetItemData(ItemID);
	for (int32 i = 0; i < ItemSlots.Num(); ++i)
	{
		const FItemSlot& Slot = ItemSlots[i];

		const bool bSameItem = (Slot.ItemId == ItemID);
		const bool bNotFull = (Slot.StackCount > 0 && Slot.StackCount < Info->MaxStackCount);

		if (bSameItem && bNotFull)
		{
			return i;
		}
	}

	return -1;
}

int32 USZInventoryComponent::FindEmptySlot() const
{
	for (int32 i = 0; i < ItemSlots.Num(); ++i)
	{
		if (ItemSlots[i].StackCount == 0)
		{
			return i;
		}
	}
	return -1;
}

void USZInventoryComponent::AddToSlot(int32 Index, int32 ItemCount)
{
	if (!ItemSlots.IsValidIndex(Index) || ItemCount <= 0)
	{
		return;
	}

	ItemSlots[Index].StackCount += ItemCount;
}

void USZInventoryComponent::AddToNewSlot(uint8 ItemID, int32 ItemCount, int32 Index)
{
	if (!ItemSlots.IsValidIndex(Index))
	{
		return;
	}

	ItemSlots[Index] = FItemSlot{ ItemID, ItemCount };
}

void USZInventoryComponent::PlayItemSFX(USoundBase* Sound) const
{
	if (Sound)
	{
		const AActor* OwnerActor = GetOwner();
		if (OwnerActor)
		{
			UGameplayStatics::PlaySoundAtLocation(this, Sound, OwnerActor->GetActorLocation());
		}
	}
}

USoundBase* USZInventoryComponent::GetItemSFX(int32 ItemID) const
{
	const TObjectPtr<FItemTemplete> Info = GetItemData(ItemID);
	if (Info)
	{
		return Info->ItemSFX.Pickup;
	}
}

int32 USZInventoryComponent::PickUp(int32 ItemID, int32 ItemCount)
{
	// 

	int32 LItemCount = FMath::Max(0, ItemCount);
	bool bLIsFull = false;

	while (LItemCount > 0 && !bLIsFull)
	{
		const int32 index = FindMatchingSlot(ItemID);

		if (index != -1 /*INDEX_NONE*/)
		{
			AddToSlot(index, 1);
		}
		else
		{
			const int32 EmptyIndex = FindEmptySlot();
			if (EmptyIndex != -1 /*INDEX_NONE*/)
			{
				AddToNewSlot(ItemID, 1, EmptyIndex);
			}
			else
			{
				bLIsFull = true;
				return ItemSlots[index].StackCount;
			}
		}

		LItemCount -= 1;
		PlayItemSFX(GetItemSFX(ItemID));
	}

	return LItemCount;
}

void USZInventoryComponent::PrintInventory()
{
	for (int32 i = 0; i < ItemSlots.Num(); ++i)
	{
		const FItemSlot Slot = ItemSlots[i];
		const FString ResultString = FString::Printf(
			TEXT("Slot %d | ItemID: %d | StackCount: %d"),
			i,
			Slot.ItemId,
			Slot.StackCount
		);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green,ResultString);
		}
	}
}

// Called when the game starts
void USZInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ItemSlots.SetNum(InventorySize);
}

// Called every frame
void USZInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


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

const FItemTemplete* USZInventoryComponent::GetItemData(FName ItemID) const
{
	if (ItemData)
	{
		return ItemData->FindRow<FItemTemplete>(ItemID, TEXT("GetItemData"));
	}
	return nullptr;
}

int32 USZInventoryComponent::FindMatchingSlot(FName ItemID) const
{
	const FItemTemplete* Item = GetItemData(ItemID);
	if (!Item) 
		return INDEX_NONE;

	for (int32 i = 0; i < ItemSlots.Num(); ++i)
	{
		const FItemSlot& Slot = ItemSlots[i];

		if (Slot.ItemID == ItemID &&
			Slot.StackCount > 0 &&
			Slot.StackCount <= Item->MaxStackCount)
		{
			return i;
		}
	}

	return INDEX_NONE;
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

void USZInventoryComponent::AddToSlot(FName ItemID, int32 Index, int32 ItemCount)
{
	if (!ItemSlots.IsValidIndex(Index) || ItemCount <= 0)
	{
		return;
	}

	const FItemTemplete* Item = GetItemData(ItemID);
	if (!Item)
		return;

	// TODO. MaxStackCount에서 남은 아이템 처리 어떻게 할지
	ItemSlots[Index].StackCount += ItemSlots[Index].StackCount;
}

void USZInventoryComponent::AddToNewSlot(FName ItemID, int32 ItemCount, int32 Index)
{
	if (!ItemSlots.IsValidIndex(Index))
	{
		return;
	}

	ItemSlots[Index].ItemID = ItemID;
	ItemSlots[Index].StackCount = ItemCount;
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

USoundBase* USZInventoryComponent::GetItemSFX(FName ItemID) const
{
	const FItemTemplete* Item = GetItemData(ItemID);
	if (Item)
	{
		return Item->ItemSFX.Pickup;
	}
	return nullptr;
}

int32 USZInventoryComponent::PickUp(FName ItemID, int32 ItemCount)
{
	int32 LItemCount = FMath::Max(0, ItemCount);
	bool bLIsFull = false;

	while (LItemCount > 0 && !bLIsFull)
	{
		const int32 index = FindMatchingSlot(ItemID);
		if (index != -1 /*INDEX_NONE*/)
		{
			AddToSlot(ItemID, index, 1);
		}
		else
		{
			const int32 EmptyIndex = FindEmptySlot();
			if (EmptyIndex != -1 /*INDEX_NONE*/)
			{
				AddToNewSlot(ItemID, 1, EmptyIndex);
			}
			/*else
			{
				bLIsFull = true;
				return ItemSlots[index].StackCount;
			}*/
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
			TEXT("Slot %d | ItemID: %s | StackCount: %d"),
			i,
			*Slot.ItemID.ToString(),
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

	ItemSlots.SetNum(MaxSlotCount);
}

// Called every frame
void USZInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


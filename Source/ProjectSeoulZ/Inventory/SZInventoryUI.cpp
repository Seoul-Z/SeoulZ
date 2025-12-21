// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SZInventoryUI.h"
#include "Components/WrapBox.h"
#include "Inventory/SZInventorySlot.h"

void USZInventoryUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	APawn* Player = GetOwningPlayerPawn();
	if (!Player) 
	{
		return;
	}

	SZInventory = Player->GetComponentByClass<USZInventoryComponent>();
	if (!SZInventory) 
	{
		return;
	}

	CreateInventorySlots();
}

void USZInventoryUI::RefreshInventory(USZInventoryComponent* InSZInventory)
{
	if (!IsValid(InSZInventory))
	{
		return;
	}

	SZInventory = InSZInventory;
	CreateInventorySlots();
}

void USZInventoryUI::CreateInventorySlots()
{
	if (!IsValid(SZInventory))
	{
		return;
	}

	WrapBox_Inventory->ClearChildren();
	for (int i = 0; i < SZInventory->ItemSlots.Num(); ++i)
	{
		FItemSlot& ItemSlot = SZInventory->ItemSlots[i];
		TObjectPtr<USZInventorySlot> SlotUI = CreateWidget<USZInventorySlot>(GetWorld(), InventorySlotClass);
		if (SlotUI)
		{
			SlotUI->ItemID = ItemSlot.ItemID;
			SlotUI->StackCount = ItemSlot.StackCount;
			SlotUI->SlotIndex = i;
			SlotUI->SZInventory = SZInventory;
			
			WrapBox_Inventory->AddChildToWrapBox(SlotUI);
		}
	}

	SZInventory->OnInventoryUpdated.AddUniqueDynamic(this, &USZInventoryUI::CreateInventorySlots);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SZInventorySlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Overlay.h"

void USZInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	SetItemData();
}

void USZInventorySlot::SetItemData()
{
	if (!IsValid(SZInventory)) 
	{
		return;
	}

	const FItemTemplete* Item = SZInventory->GetItemData(ItemID);
	if (!Item) 
	{
		Overlay_InventorySlot->SetVisibility(ESlateVisibility::Collapsed);
	}
	else 
	{
		TObjectPtr<UTexture2D> Icon = SZInventory->GetItemData(ItemID)->Icon;
		if (Icon)
		{
			Img_ItemIcon->SetBrushFromTexture(Icon);
		}

		Txt_StackCount->SetText(FText::AsNumber(StackCount));
		Overlay_InventorySlot->SetVisibility(ESlateVisibility::Visible);
	}
}

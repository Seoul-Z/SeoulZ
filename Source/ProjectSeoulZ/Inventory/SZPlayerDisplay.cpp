// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SZPlayerDisplay.h"
#include "Player/SZPlayerController.h"
#include "Player/Components/SZInventoryComponent.h"

void USZPlayerDisplay::NativePreConstruct()
{
	Super::NativePreConstruct();

	DisplayInventory();
}

void USZPlayerDisplay::NativeConstruct()
{
	Super::NativeConstruct();

	ShowMouse();
}

void USZPlayerDisplay::NativeDestruct()
{
	Super::NativeDestruct();

	HideMouse();
}

void USZPlayerDisplay::ShowMouse()
{
	ASZPlayerController* SZPC = GetOwningPlayer<ASZPlayerController>();
	if (!IsValid(SZPC)) 
	{
		return;
	}

	SZPC->bShowMouseCursor = true;

	FInputModeGameAndUI InputMode; // Game And UI
	InputMode.SetWidgetToFocus(this->TakeWidget()); // 우선 순위는 UI
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 마우스 뷰 포트 밖으로 이동 가능
	InputMode.SetHideCursorDuringCapture(true);
	
	SZPC->SetInputMode(InputMode);
}

void USZPlayerDisplay::HideMouse()
{
	ASZPlayerController* SZPC = GetOwningPlayer<ASZPlayerController>();
	if (!IsValid(SZPC))
	{
		return;
	}

	SZPC->bShowMouseCursor = false;

	FInputModeGameOnly InputMode;
	SZPC->SetInputMode(InputMode);
}

void USZPlayerDisplay::DisplayInventory()
{
	ASZPlayerController* SZPC = GetOwningPlayer<ASZPlayerController>();
	if (!IsValid(SZPC))
	{
		return;
	}

	USZInventoryComponent* SZInventory = Cast<USZInventoryComponent>(SZPC->GetComponentByClass(USZInventoryComponent::StaticClass()));
	if (!IsValid(SZInventory))
	{
		return;
	}

	WB_InventoryUI->RefreshInventory(SZInventory);
}

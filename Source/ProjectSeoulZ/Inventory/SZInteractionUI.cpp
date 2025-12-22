// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SZInteractionUI.h"
#include "Components/TextBlock.h"

void USZInteractionUI::NativePreConstruct()
{
	Txt_Interact->SetText(Message);
	SetVisibility(Txt_Interact->GetText().IsEmpty()? 
		ESlateVisibility::Collapsed
		: ESlateVisibility::SelfHitTestInvisible);
}

void USZInteractionUI::SetMessage(const FText& InMessage)
{
	Message = InMessage;

	Txt_Interact->SetText(Message);
	SetVisibility(Txt_Interact->GetText().IsEmpty() ?
		ESlateVisibility::Collapsed
		: ESlateVisibility::SelfHitTestInvisible);
}
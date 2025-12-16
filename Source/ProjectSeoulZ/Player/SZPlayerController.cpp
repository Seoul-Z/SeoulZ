// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SZPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"

void ASZPlayerController::ShowPlayerHud()
{
	if (PlayerHUDClass)
	{
		PlayerHUD = CreateWidget<UUserWidget>(this, PlayerHUDClass);

		if (PlayerHUD) 
		{
			PlayerHUD->AddToViewport();
		}
	}
}

void ASZPlayerController::BeginPlay()
{
	ShowPlayerHud();
}

void ASZPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(CurrentCharacterContext, 0);
		}
	}
}

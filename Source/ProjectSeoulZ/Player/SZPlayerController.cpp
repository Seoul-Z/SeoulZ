// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SZPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/SZWardrobe.h"
#include "Inventory/SZInventoryActor.h"

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

void ASZPlayerController::ToggleInventory()
{
	if (IsValid(InventoryActor))
	{
		InventoryActor->CloseInventory();
	}
	else
	{
		InventoryActor = CreateInventoryActor();

		if (IsValid(InventoryActor))
		{
			InventoryActor->OpenInventory();
		}
	}
}

FSpawnWardrobeResult ASZPlayerController::CreateWardrobeActor()
{
	FSpawnWardrobeResult Out;

	const FVector SpawnLoc(0.f, 0.f, 1000000.f);
	const FRotator SpawnRot(0.f, 0.f, 0.f);
	const FTransform SpawnTM(SpawnRot, SpawnLoc, FVector(1.f));

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetPawn();
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (!WardrobeClass)
	{
		return Out;
	}

	ASZWardrobe* Spawned = GetWorld()->SpawnActor<ASZWardrobe>(WardrobeClass, SpawnTM, Params);
	WardrobeActor = Spawned;

	Out.Transform = SpawnTM;
	Out.WardrobeActor = Spawned;
	return Out;
}

ASZInventoryActor* ASZPlayerController::CreateInventoryActor()
{
	if (!IsValid(WardrobeActor))
	{
		CreateWardrobeActor();
	}

	const FTransform SpawnTM = WardrobeActor->GetActorTransform();

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetPawn();
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (!InventoryActorClass)
	{
		return nullptr;
	}

	ASZInventoryActor* Spawned =
		GetWorld()->SpawnActorDeferred<ASZInventoryActor>(InventoryActorClass, SpawnTM, nullptr, nullptr,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	if (!IsValid(Spawned))
	{
		return nullptr;
	}

	Spawned->WardrobeActor = WardrobeActor;
	Spawned->FinishSpawning(SpawnTM);
	InventoryActor = Spawned;

	return Spawned;
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

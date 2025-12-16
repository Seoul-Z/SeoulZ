// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SZLobbyMode.h"

void ASZLobbyMode::BeginPlay()
{
	Super::BeginPlay();

	// 현재 GameInstance가 있는지 체크. 없으면 가져오기.
	if (!CachedGameInstance)
	{
		CachedGameInstance = Cast<USZGameInstance>(GetGameInstance());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Errpr: %s"), TEXT("There is No GameInstance"));
	}

	// 현재 GameInstance가 있는지 체크 후 GameSettings 적용.
	if (CachedGameInstance)
	{
		ApplyGameSettings();
		UE_LOG(LogTemp, Log, TEXT("Errpr: %s"), TEXT("Settings Applied"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Errpr: %s"), TEXT("There is No GameInstance"));
	}
}

// @Todo: 인자 추가해야댐
void ASZLobbyMode::ApplyGameSettings()
{
	switch (CachedGameInstance->CurrentGameMode)
	{
	case EGameModeType::Lobby:
		UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("Lobby Mode Started"));
		break;
	case EGameModeType::Playing	:
		UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("Playing Mode Started"));
		break;
	default:
		UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("Game Mode is not Started"));
		break;
	}
}

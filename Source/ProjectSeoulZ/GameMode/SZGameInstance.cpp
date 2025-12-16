// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SZGameInstance.h"
#include "SZGameInstance.h"

USZGameInstance::USZGameInstance()
{
	CurrentGameMode = EGameModeType::Lobby;
}

void USZGameInstance::SetGameMode(EGameModeType InMode)
{
	CurrentGameMode = InMode;
}

void USZGameInstance::SetMap(FName InName)
{
	CurrentMapName = InName;
}

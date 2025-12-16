// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SZGameInstance.generated.h"

/**
 * 
 */

// 게임 모드 열거형.
UENUM(BlueprintType)
enum class EGameModeType : uint8
{
	Lobby UMETA(DisplayName = "Lobby"),
	Playing UMETA(DisplayName = "Playing")
};

UCLASS()
class PROJECTSEOULZ_API USZGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USZGameInstance();

	UFUNCTION(BlueprintCallable)
	void SetGameMode(EGameModeType InGameMode);

	UFUNCTION(BlueprintCallable)
	void SetMap(FName InName);

public:
	// 현재 게임 모드.
	UPROPERTY(BlueprintReadWrite, Category = "Game Settings")
	EGameModeType CurrentGameMode;
	
	// 현재 게임 맵.
	UPROPERTY(BlueprintReadWrite, Category = "Game Settings")
	FName CurrentMapName;
	

};

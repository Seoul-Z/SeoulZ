// Fill out your copyright notice in the Description page of Project Settings.

//﻿---------------------------------------------------------------------------------------------------------
// Author		: 안재범
// Date			: 2025-12-15
// Copyright	: CodingDead
// Description	: GameInstance 클래스.
//				  레벨 불러오는 용도.
//----------------------------------------------------------------------------------------------------------

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

	// 선택한 맵을 바탕으로 레벨을 불러온다.
	UFUNCTION(BlueprintCallable)
	void OpenLevel(FName InSelectedMapName);

public:
	// 게임 맵 배열.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> MapNames;

	// 선택된 게임 맵.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
	FName SelectedMapName;


};

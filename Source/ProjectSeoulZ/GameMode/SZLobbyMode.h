// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SZGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "SZLobbyMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSEOULZ_API ASZLobbyMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	void ApplyGameSettings();

protected:
	UPROPERTY()
	USZGameInstance* CachedGameInstance;

};

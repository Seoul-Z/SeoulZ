// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "SZPlayerController.generated.h"

//---------------------------------------------------------------------------------------------------------
// Author       : 박지훈, 이혜성, 고미소
// Date         : 2025-12-15
// Copyright    : 
//
// Description  : PlayerController 클래스 
//               IMC 연동 및 Inventory 보여주는 기능을 담당
//				 
//                 
//----------------------------------------------------------------------------------------------------------


class ASZWardrobe;
class ASZInventoryActor;

USTRUCT(BlueprintType)
struct FSpawnWardrobeResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FTransform Transform;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ASZWardrobe> WardrobeActor = nullptr;
};

/**
 * 
 */
UCLASS()
class PROJECTSEOULZ_API ASZPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void ShowPlayerHud();
	void ToggleInventory();
	FSpawnWardrobeResult CreateWardrobeActor();
	ASZInventoryActor* CreateInventoryActor();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUserWidget> PlayerHUD;

protected:
	// 연동
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<ASZWardrobe> WardrobeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<ASZInventoryActor> InventoryActorClass;

	// 캐싱
	UPROPERTY(VisibleInstanceOnly, Category = "Spawn")
	TObjectPtr<ASZWardrobe> WardrobeActor;

	UPROPERTY(VisibleInstanceOnly, Category = "Spawn")
	TObjectPtr<ASZInventoryActor> InventoryActor;
 
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMC", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> CurrentCharacterContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PlayerHUDClass;
};

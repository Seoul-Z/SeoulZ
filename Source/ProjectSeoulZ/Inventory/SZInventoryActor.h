// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Inventory/SZPlayerDisplay.h"
#include "Inventory/SZWardrobe.h"
#include "SZInventoryActor.generated.h"

//---------------------------------------------------------------------------------------------------------
// Author       : 고미소
// Date         : 2025-12-22
// Copyright    : 
//
// Description  : Inventory 액터 
//               인벤토리/장비 디스플레이를 보여주기 위한 액터
//               - InventoryUI로 단순히 디스플레이를 띄울 수 있으나, 추후 옷장(워드로브) 앞에서만 장비 변경 등 보여주는 것과 관련된 기능을 쉽게 붙이려고 Actor로 분리
//----------------------------------------------------------------------------------------------------------


class ASZPlayerController;

UCLASS()
class PROJECTSEOULZ_API ASZInventoryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASZInventoryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreatePlayerDisplay();
	void OpenInventory();
	void CloseInventory();

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Actors", meta = (ExposeOnSpawn = "true", AllowPrivateAccess = "true"))
	TObjectPtr<class ASZWardrobe> WardrobeActor;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureComp;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USZPlayerDisplay> PlayerDisplayClass;

	UPROPERTY(Transient)
	TObjectPtr<USZPlayerDisplay> PlayerDisplay;

private:
	ASZPlayerController* SZPC;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/SZInteractionInterface.h"
#include "Item/Components/SZItemDataComp.h"	
#include "SZItemBase.generated.h"

//---------------------------------------------------------------------------------------------------------
// Author       : 고미소
// Date         : 2025-12-17
// Copyright    : Coding Dead
//
// Description  : Item Base 액터 클래스
//               Item Data Component를 포함하는 기본 아이템 액터 클래스
//                 
//----------------------------------------------------------------------------------------------------------


UCLASS()
class PROJECTSEOULZ_API ASZItemBase : public AActor, public ISZInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASZItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USZItemDataComp> ItemDataComp;
};

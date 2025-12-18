// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/SZInteractionInterface.h"
#include "SZItemDataComp.generated.h"

//---------------------------------------------------------------------------------------------------------
// Author       : 고미소
// Date         : 2025-12-17
// Copyright    : Coding Dead
//
// Description  : Item Data 컴포넌트
//               상호작용 인터페이스를 상속받아 아이템 상호작용 기능을 구현
//                 
//----------------------------------------------------------------------------------------------------------


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSEOULZ_API USZItemDataComp : public UActorComponent, public ISZInteractionInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USZItemDataComp();

	virtual void OnInteractWith_Implementation(AActor* Interactor) override;
	virtual FText OnLookAt_Implementation() const override;

	void PickUpItem(AActor* InItem);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item, Meta = (AllowPrivateAccess = "true"))
	FDataTableRowHandle ItemRowHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item, Meta = (AllowPrivateAccess = "true"))
	int32 StackCount = 1;
};

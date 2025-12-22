// Fill out your copyright notice in the Description page of Project Settings.


#include "SZItemDataComp.h"
#include "Player/Components/SZInventoryComponent.h"
#include "Item/SZItemBase.h"

// Sets default values for this component's properties
USZItemDataComp::USZItemDataComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USZItemDataComp::OnInteractWith_Implementation(AActor* Interactor)
{
	PickUpItem(Interactor);
}

FText USZItemDataComp::OnLookAt_Implementation() const
{
	return FText();
}

void USZItemDataComp::PickUpItem(AActor* Interactor)
{
	USZInventoryComponent* InventoryComp = Interactor? 
		Interactor->FindComponentByClass<USZInventoryComponent>() : nullptr;
	if (!IsValid(InventoryComp)) 
	{
		return;
	}

	ASZItemBase* ItemOwner = Cast<ASZItemBase>(GetOwner());
	if (!IsValid(ItemOwner))
	{
		return;
	}

	FName ItemID = ItemOwner->GetItemID();
	int32 N = InventoryComp->PickUp(ItemID, StackCount);
	// TODO. 아이템 파괴 대신, 오브젝트 폴링으로 코드 변경
	GetOwner()->Destroy();
}

// Called when the game starts
void USZItemDataComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void USZItemDataComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


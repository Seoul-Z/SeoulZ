// Fill out your copyright notice in the Description page of Project Settings.


#include "SZItemDataComp.h"
#include "Player/Components/SZInventoryComponent.h"

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

void USZItemDataComp::PickUpItem(AActor* InInteractor)
{
	// TODO. 아이템 파괴 대신, 오브젝트 폴링
	// GetOwner()->Destroy(); 
	
	TObjectPtr<USZInventoryComponent> InventoryComp = Interactor->FindComponentByClass<USZInventoryComponent>();
	if (IsValid(InventoryComp))
	{
		/*const FName ItemID = ItemData.RowName;
		const int32 Quantity = ItemQuantity;
		InventoryComp->PickUp(ItemID, ItemQuantity);
		GetOwner()->Destroy();
		bool bSuccess = InventoryComp->PickUp(ItemID, Quantity);

		if (bSuccess)
		{
			Destroy();
		}*/
	}
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


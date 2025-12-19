// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SZItemBase.h"

// Sets default values
ASZItemBase::ASZItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(StaticMeshComp);

	ItemDataComp = CreateDefaultSubobject<USZItemDataComp>(TEXT("ItemDataComp"));
}

const FName ASZItemBase::GetItemID() const 
{
	return ItemDataHandle.RowName;
}

const FItemTemplete* ASZItemBase::GetItemData() const
{
	return ItemDataHandle.GetRow<FItemTemplete>(TEXT("GetItemData"));
}

FText ASZItemBase::OnLookAt_Implementation() const
{
	if (const FItemTemplete* Data = GetItemData())
	{
		return FText::Format(FText::FromString(TEXT("{0} 줍기")), Data->Name);
	}
	return FText::GetEmpty();
}

void ASZItemBase::SetStaticMesh()
{
	if (GetItemData()) 
	{
		TObjectPtr<UStaticMesh> SM = GetItemData()->ItemMesh.StaticMesh;
		if (SM)
		{
			StaticMeshComp->SetStaticMesh(SM);
		}
	}
}

void ASZItemBase::SetMaterial()
{
}

// Called when the game starts or when spawned
void ASZItemBase::BeginPlay()
{
	Super::BeginPlay();

}

void ASZItemBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// 메쉬가 있을 때만 물리 시뮬레이션
	if (StaticMeshComp && StaticMeshComp->GetStaticMesh())
	{
		StaticMeshComp->SetSimulatePhysics(true);
	}

	SetStaticMesh();
}

// Called every frame
void ASZItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


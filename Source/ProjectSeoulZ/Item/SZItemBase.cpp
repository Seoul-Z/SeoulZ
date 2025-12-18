// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SZItemBase.h"

// Sets default values
ASZItemBase::ASZItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemDataComp = CreateDefaultSubobject<USZItemDataComp>(TEXT("ItemDataComp"));
}

// Called when the game starts or when spawned
void ASZItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ASZItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


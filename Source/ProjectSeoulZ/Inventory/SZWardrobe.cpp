// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SZWardrobe.h"

// Sets default values
ASZWardrobe::ASZWardrobe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character"));
	CharacterMesh->SetupAttachment(Root);

	Vest = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Vest"));
	Vest->SetupAttachment(CharacterMesh);

	Gloves = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gloves"));
	Gloves->SetupAttachment(CharacterMesh);

	Holster = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Holster"));
	Holster->SetupAttachment(CharacterMesh);

	Magazine = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Magazine"));
	Magazine->SetupAttachment(CharacterMesh);

}

void ASZWardrobe::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!IsValid(CharacterMesh))
	{
		return;
	}

	auto Equipment = [&](USkeletalMeshComponent* Follower)
		{
			if (!IsValid(Follower) || Follower == CharacterMesh)
			{
				return;
			}
			const bool bForceUpdate = true;
			const bool bFollowerShouldTickPose = false;

			Follower->SetLeaderPoseComponent(CharacterMesh, bForceUpdate, bFollowerShouldTickPose);
			// Follower->bUpdateAnimationInEditor = false;
			// Follower->SetAnimationMode(EAnimationMode::AnimationBlueprint); 
		};

	Equipment(Vest);
	Equipment(Gloves);
	Equipment(Holster);
	Equipment(Magazine);
}

// Called when the game starts or when spawned
void ASZWardrobe::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASZWardrobe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


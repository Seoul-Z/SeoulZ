// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SZWardrobe.generated.h"

//---------------------------------------------------------------------------------------------------------
// Author       : 고미소
// Date         : 2025-12-22
// Copyright    : 
//
// Description  : Wardrobe 액터 
//               플레이어 외형 변경을 관리하는 전용 액터로, Inventory 액터에서 사용됨.
//                 
//----------------------------------------------------------------------------------------------------------

UCLASS()
class PROJECTSEOULZ_API ASZWardrobe : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASZWardrobe();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
	TObjectPtr<USceneComponent> Root;

	// 캐릭터 메쉬 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes")
	TObjectPtr<USkeletalMeshComponent> CharacterMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes")
	TObjectPtr<USkeletalMeshComponent> Vest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes")
	TObjectPtr<USkeletalMeshComponent> Gloves;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes")
	TObjectPtr<USkeletalMeshComponent> Holster;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes")
	TObjectPtr<USkeletalMeshComponent> Magazine;
};

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"  
#include "SZItemDefine.h"
#include "SZItemTemplete.generated.h"

class ASZItemBase;
class UGameplayEffect;
class USoundBase;
class USkeletalMesh;
class UStaticMesh;
class UMaterialInterface;
class UTexture2D;

USTRUCT(BlueprintType)
struct FItemMesh : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BP_Item")
	TSubclassOf<ASZItemBase> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<UStaticMesh> StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TArray<TObjectPtr<UMaterialInterface>> Materials;
};

USTRUCT(BlueprintType)
struct FItemFragment : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GE")
	TArray<TSubclassOf<UGameplayEffect>> Fragments;
};

USTRUCT(BlueprintType)
struct FItemSFX : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<USoundBase> Pickup = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<USoundBase> Drop = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<USoundBase> Move = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<USoundBase> Use = nullptr;
};

USTRUCT(BlueprintType)
struct FItemEquipment : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentType EquipmentType = EEquipmentType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentSlotType EquipmentSlotType = EEquipmentSlotType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Defense = 0;
};

USTRUCT(BlueprintType)
struct FItemConsumpables : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HealthAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnergyAmount = 0;
};

USTRUCT(BlueprintType)
struct FItemTemplete : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemMesh ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemFragment ItemFragment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemSFX ItemSFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemCategory ItemCategory = EItemCategory::Misc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemEquipment Equipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemConsumpables Consumpables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemRarity ItemRarity = EItemRarity::Common;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStackCount = 1;
};

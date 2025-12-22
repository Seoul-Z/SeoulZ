#pragma once

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Weapons,
	Appeal,
	Consumables,
	Misc
};

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	None,
	Weapon,
	Appeal,

	Count	UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EEquipmentSlotType : uint8
{
	None,
	Gun_Primary,
	Gun_Secondary,
	Helemet,
	Vest,
	Magazine,
	Gloves,
	Holster,

	Count	UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common,
	Uncommon,
	Rare,
	Legendary,

	Count	UMETA(Hidden)
};
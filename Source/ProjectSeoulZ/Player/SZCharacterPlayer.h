// Fill out your copyright notice in the Description page of Project Settings.

//---------------------------------------------------------------------------------------------------------
// Author       : 박지훈
// Date       : 2025-12-15
// Copyright   : 
//
// Description : CharacterPlayer 클래스 
//               플레이어의 전반적인 동작을 관할하는 클래스
//				 
//                 
//----------------------------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Character/SZCharacterBase.h"
#include "AbilitySystemInterface.h"
#include "InputActionValue.h"
#include "SZCharacterPlayer.generated.h"

class ASZPlayerController;
class USZInteractionComp;
class USZInventoryComponent;

UENUM()
enum class ECharacterControlType : uint8
{
	ThirdPerson,
	FirstPerson
};

/**
 * 
 */
UCLASS()
class PROJECTSEOULZ_API ASZCharacterPlayer : public ASZCharacterBase
{
	GENERATED_BODY()
	
public:
	ASZCharacterPlayer();

	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// 캐릭터 게임 시작 및 죽음
	virtual void BeginPlay() override;
	virtual void SetDead() override;

	// 캐릭터 컨트롤
	void ChangeCharacterControl();
	void SetCharacterControl(ECharacterControlType NewCharacterControlType);
	void SetCharacterControlData(const class USZCharacterControlData* CharacterControlData);

	// 카메라/이동 세팅 적용 (필요 시 분리)
	void ApplyThirdPersonSettings(bool bInstant = false);
	void ApplyFirstPersonSettings(bool bInstant = false);

protected:
	// 카메라
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Mode")
	ECharacterControlType CurrentControlType = ECharacterControlType::ThirdPerson;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

	// TPS 카메라 (현재 FollowCamera를 TPS로 쓰는 편이 자연스러움)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> ThirdPersonCamera;

	// FPS 카메라 (캐릭터 머리/눈 위치에 부착)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	// 3인칭 파라미터
	UPROPERTY(EditAnywhere, Category = "Camera|Third")
	float ThirdArmLength = 400.f;

	UPROPERTY(EditAnywhere, Category = "Camera|Third")
	FVector ThirdSocketOffset = FVector(0.f, 60.f, 70.f); // 어깨 카메라 느낌

	// 1인칭 파라미터
	UPROPERTY(EditAnywhere, Category = "Camera|First")
	FVector FirstPersonRelativeLocation = FVector(0.f, 0.f, 64.f);

	UPROPERTY(EditAnywhere, Category = "Camera|Blend")
	float CameraBlendSpeed = 12.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ChangeControlAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MouseLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ThirdMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ThirdLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> FirstMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> FirstLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SkillAction;

	// 아이템 줍기 - 입력 값
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> PickUpAction;

	// 인벤토리 열기 - 입력 값
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> InventoryAction;

	void Move(const FInputActionValue& Value);
	void MouseLook(const FInputActionValue& Value);

	void ThirdMove(const FInputActionValue& Value);
	void ThirdLook(const FInputActionValue& Value);

	void FirstMove(const FInputActionValue& Value);
	void FirstLook(const FInputActionValue& Value);

	// 아이템 줍기
	void PickUp(const FInputActionValue& Value);
	// 인벤토리 열고 닫기
	void ToggleInventory(const FInputActionValue& Value);

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// 캐릭터 메쉬 컴포넌트
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes")
	// TObjectPtr<USkeletalMeshComponent> FullBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes")
	TObjectPtr<USkeletalMeshComponent> Helmet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes")
	TObjectPtr<USkeletalMeshComponent> Vest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes")
	TObjectPtr<USkeletalMeshComponent> Gloves;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes")
	TObjectPtr<USkeletalMeshComponent> Holster;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes")
	TObjectPtr<USkeletalMeshComponent> Magazine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes")
	TObjectPtr<USkeletalMeshComponent> PrimaryWeapon;

private:
	bool bWantsBlend = false;
	float BlendAlpha = 1.0f; // 0=3인칭, 1=1인칭
	ECharacterControlType TargetControlType = ECharacterControlType::ThirdPerson;

	// 플레이어 컨트롤러
	UPROPERTY(Transient)
	TObjectPtr<ASZPlayerController> SZPC;
	// 상호작용 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USZInteractionComp> SZInteraction;
	// 인벤토리 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USZInventoryComponent> SZInventory;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SZCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/SZCharacterControlData.h"
#include "GameFramework/CharacterMovementComponent.h"

ASZCharacterPlayer::ASZCharacterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = ThirdArmLength;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bDoCollisionTest = true;

	// TPS 카메라 (기존 FollowCamera 역할)
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	ThirdPersonCamera->bUsePawnControlRotation = false;

	// FPS 카메라 (캐릭터 Mesh에 붙이거나, Root에 붙이고 상대위치로 조정)
	// 보통은 Mesh(Head 소켓)에 붙이는 방식이 가장 깔끔합니다.
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetMesh()); // 또는 RootComponent
	FirstPersonCamera->SetRelativeLocation(FirstPersonRelativeLocation);
	FirstPersonCamera->bUsePawnControlRotation = true;

	// 처음에는 TPS만 활성
	ThirdPersonCamera->SetActive(true);
	FirstPersonCamera->SetActive(false);

	// Input
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Game/Input/IMC_Default.IMC_Default"));
	if (nullptr != InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Game/Input/Actions/IA_Move.IA_Move"));
	if (nullptr != InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Game/Input/Actions/IA_Jump.IA_Jump"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Game/Input/Actions/IA_Look.IA_Look"));
	if (nullptr != InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputChangeActionControlRef(TEXT("/Game/Input/Actions/IA_ChangeControl.IA_ChangeControl"));
	if (nullptr != InputChangeActionControlRef.Object)
	{
		ChangeControlAction = InputChangeActionControlRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMouseLookRef(TEXT("/Game/Input/Actions/IA_MouseLook.IA_MouseLook"));
	if (nullptr != InputActionMouseLookRef.Object)
	{
		MouseLookAction = InputActionMouseLookRef.Object;
	}

}

void ASZCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent called: %s"), *GetName());

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent=%s"), EIC ? TEXT("VALID") : TEXT("NULL"));

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);


	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASZCharacterPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Ongoing, this, &ASZCharacterPlayer::Look);
	EnhancedInputComponent->BindAction(ChangeControlAction, ETriggerEvent::Started, this, &ASZCharacterPlayer::ChangeCharacterControl);

}

void ASZCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	CurrentControlType = ECharacterControlType::ThirdPerson;
	ApplyThirdPersonSettings(true);

	UE_LOG(LogTemp, Warning, TEXT("IMC Added: %s"), *GetNameSafe(DefaultMappingContext));

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		//Subsystem->RemoveMappingContext(DefaultMappingContext);
	}

}

void ASZCharacterPlayer::SetDead()
{
}

void ASZCharacterPlayer::ChangeCharacterControl()
{
	const ECharacterControlType NewType =
		(CurrentControlType == ECharacterControlType::ThirdPerson)
		? ECharacterControlType::FirstPerson
		: ECharacterControlType::ThirdPerson;

	SetCharacterControl(NewType);

}

void ASZCharacterPlayer::SetCharacterControl(ECharacterControlType NewCharacterControlType)
{
	if (CurrentControlType == NewCharacterControlType)
		return;

	AController* PlayerControllerCon = GetController();

	const FRotator SavedControlRotation = PlayerControllerCon ? PlayerControllerCon->GetControlRotation() : FRotator::ZeroRotator;

	CurrentControlType = NewCharacterControlType;

	// 즉시 전환
	if (NewCharacterControlType == ECharacterControlType::ThirdPerson)
	{
		ApplyThirdPersonSettings(true);
	}
	else
	{
		ApplyFirstPersonSettings(true);
	}

	if (PlayerControllerCon)
	{
		PlayerControllerCon->SetControlRotation(SavedControlRotation);
	}
}

void ASZCharacterPlayer::ApplyThirdPersonSettings(bool bInstant)
{
	FirstPersonCamera->SetActive(false);
	ThirdPersonCamera->SetActive(true);

	// 스프링암 세팅
	CameraBoom->TargetArmLength = ThirdArmLength;
	CameraBoom->SocketOffset = ThirdSocketOffset;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bDoCollisionTest = true;

	// 3인칭에서 보통: 캐릭터는 이동 방향으로 회전하고, 컨트롤 회전은 카메라만
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
}

void ASZCharacterPlayer::ApplyFirstPersonSettings(bool bInstant)
{
	// 카메라 활성화
	ThirdPersonCamera->SetActive(false);
	FirstPersonCamera->SetActive(true);

	// 1인칭에서는 스프링암을 사실상 “무력화”하는 편이 안전
	CameraBoom->TargetArmLength = 0.f;
	CameraBoom->SocketOffset = FVector::ZeroVector;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bDoCollisionTest = false;

	// 1인칭에서 보통: 컨트롤 Yaw가 곧 캐릭터 Yaw
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 0.f);
}

void ASZCharacterPlayer::SetCharacterControlData(const USZCharacterControlData* CharacterControlData)
{
	CameraBoom->TargetArmLength = CharacterControlData->TargetArmLength;
	CameraBoom->SetRelativeRotation(CharacterControlData->RelativeRotation);
	CameraBoom->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	CameraBoom->bInheritPitch = CharacterControlData->bInheritPitch;
	CameraBoom->bInheritYaw = CharacterControlData->bInheritYaw;
	CameraBoom->bInheritRoll = CharacterControlData->bInheritRoll;
	CameraBoom->bDoCollisionTest = CharacterControlData->bDoCollisionTest;
}

void ASZCharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void ASZCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (!LookAxisVector.IsNearlyZero())
	{
		UE_LOG(LogTemp, Warning, TEXT("Look V=(%f,%f)"), LookAxisVector.X, LookAxisVector.Y);
	}

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ASZCharacterPlayer::MouseLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (!LookAxisVector.IsNearlyZero())
	{
		UE_LOG(LogTemp, Warning, TEXT("Look V=(%f,%f)"), LookAxisVector.X, LookAxisVector.Y);
	}

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ASZCharacterPlayer::ThirdMove(const FInputActionValue& Value)
{
}

void ASZCharacterPlayer::ThirdLook(const FInputActionValue& Value)
{
}

void ASZCharacterPlayer::FirstMove(const FInputActionValue& Value)
{
}

void ASZCharacterPlayer::FirstLook(const FInputActionValue& Value)
{
}

UAbilitySystemComponent* ASZCharacterPlayer::GetAbilitySystemComponent() const
{
	return nullptr;
}

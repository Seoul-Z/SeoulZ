// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SZInventoryActor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SZPlayerController.h"

// Sets default values
ASZInventoryActor::ASZInventoryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// 각 컴포넌트에 대한 디테일한 설정은 BP에서 설정함.
	// SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Root);
	// SceneCapture
	SceneCaptureComp = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComp"));
	SceneCaptureComp->SetupAttachment(SpringArm); 
	SceneCaptureComp->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;

	// PlayerController
	SZPC = Cast<ASZPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!IsValid(SZPC))
	{
		return;
	}
}

// Called when the game starts or when spawned
void ASZInventoryActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASZInventoryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASZInventoryActor::CreatePlayerDisplay()
{
	if (PlayerDisplayClass) 
	{
		PlayerDisplay = CreateWidget<USZPlayerDisplay>(SZPC, PlayerDisplayClass);

		if (PlayerDisplay) 
		{
			PlayerDisplay->AddToViewport();
		}
	}
}

void ASZInventoryActor::OpenInventory()
{
	SceneCaptureComp->ShowOnlyActorComponents(WardrobeActor);
	CreatePlayerDisplay();
	DisableInput(SZPC);
	EnableInput(SZPC);
}


void ASZInventoryActor::CloseInventory()
{
	if (!IsValid(PlayerDisplay))
	{
		return;
	}

	PlayerDisplay->RemoveFromParent();
	WardrobeActor = nullptr;
	DisableInput(SZPC);
	EnableInput(SZPC);
	Destroy();
}


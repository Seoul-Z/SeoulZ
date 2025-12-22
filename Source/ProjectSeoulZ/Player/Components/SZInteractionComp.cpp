// Fill out your copyright notice in the Description page of Project Settings.


#include "SZInteractionComp.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SZPlayerController.h"
#include "Blueprint/WidgetTree.h"
#include "Interface/SZInteractionInterface.h"

// Sets default values for this component's properties
USZInteractionComp::USZInteractionComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

USZInteractionUI* USZInteractionComp::GetInteractionUI() const
{
	ASZPlayerController* SZPC = Cast<ASZPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (SZPC) 
    {
        if (UUserWidget* InteractionUI = SZPC->PlayerHUD->WidgetTree->FindWidget<UUserWidget>(TEXT("WB_InteractionUI")))
        {
            return Cast<USZInteractionUI>(InteractionUI);
        }
    }
    
    return nullptr;
}

void USZInteractionComp::InteractionTrace()
{
    USZInteractionUI* UI = GetInteractionUI();
    
#pragma region 충돌
    FHitResult Hit;

    const FVector Start = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 50.f - FVector(0.f, 0.f, 10.f);;
    const FVector End = Start + GetOwner()->GetActorForwardVector() * 100.f;

    const FQuat CapsuleQuat = FRotationMatrix::MakeFromZ(GetOwner()->GetActorForwardVector()).ToQuat();

    const float CapsuleRadius = 88.f;  // 넓이
    const float CapsuleHalfHeight = 120.f;  // 길이
    const FCollisionShape Shape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight);

    FCollisionQueryParams Params(SCENE_QUERY_STAT(InteractionTrace), false);
    Params.AddIgnoredActor(GetOwner());

    const bool bHit = GetWorld()->SweepSingleByChannel(
        Hit, Start, End, CapsuleQuat, ItemTraceChannel, Shape, Params
    );
#pragma endregion

    AActor* HitActor = Hit.GetActor();
    if (bHit && HitActor)
    {
      if (HitActor->GetClass()->ImplementsInterface(USZInteractionInterface::StaticClass()))
      {
            Item = HitActor;
            if (UI) 
            { 
                UI->SetMessage(ISZInteractionInterface::Execute_OnLookAt(Item));
            }
      }
    }
    else 
    {
        UI->SetMessage(FText::GetEmpty());
		// 이후 USZInteractionUI에서 메시지가 비어있으면 아이템 정보 안 뜨도록 처리
    }

#pragma region 디버그
    const FVector CapsuleOrigin = (Start + End) * 0.5f;
    DrawDebugCapsule(
        GetWorld(),
        CapsuleOrigin,
        CapsuleHalfHeight,
        CapsuleRadius,
        CapsuleQuat,
        bHit ? FColor::Green : FColor::Red,
        false,
        1.f,
        0,
        1.f
    );
#pragma endregion
}

void USZInteractionComp::PickUpItem()
{
    if (!Item)
    {
        return;
	}

    // Item을 주웠을 시 
    USZItemDataComp* ItemDataComp = Item->FindComponentByClass<USZItemDataComp>();
    if (ItemDataComp)
    {
		// ItemDataComp의 OnInteractWith 실행
        ISZInteractionInterface::Execute_OnInteractWith(ItemDataComp, GetOwner());
    }
}

// Called when the game starts
void USZInteractionComp::BeginPlay()
{
	Super::BeginPlay();

	BeginInteract();
}

void USZInteractionComp::BeginInteract()
{
    // Tick 대신 Timer로 상호작용 처리
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle,
        this,
        &USZInteractionComp::UpdateInteract,
        0.1f,
        true
    );
}

void USZInteractionComp::UpdateInteract()
{
    InteractionTrace();
}


// Called every frame
void USZInteractionComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


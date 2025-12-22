// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/SZNormalMonster.h"
#include "SZNormalMonster.h"
#include "AI/SZNormalAIController.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Monster/GA/SZGA_NormalAttack.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Attribute/SZAttributeSet.h"
#include "UI/SZWidgetComponent.h"
#include "UI/SZUserWidget.h"
#include "UI/SZHpBarUserWidget.h"

ASZNormalMonster::ASZNormalMonster()
{
	AIControllerClass = ASZNormalAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Animation/ABP_NormalMonster.ABP_NormalMonster_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<USZAttributeSet>(TEXT("AttributeSet"));

	HpBar = CreateDefaultSubobject<USZWidgetComponent>(TEXT("Widget"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 8.0f));
	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetRef(TEXT("/Game/UI/HUD/WBP_HpBar.WBP_HpBar_C"));
	if (HpBarWidgetRef.Class)
	{
		HpBar->SetWidgetClass(HpBarWidgetRef.Class);
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetDrawSize(FVector2D(200.0f, 30.f));
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}
}


// 밑의 네가지 함수들은 나중에 AttributeSet으로 교체가능성 있음.
float ASZNormalMonster::GetAIPatrolRadius()
{
	return 1500.0f;
}

float ASZNormalMonster::GetAIDetectRange()
{
	return 400.0f;
}

float ASZNormalMonster::GetAIAttackRange()
{
	return 200.0f;
}

float ASZNormalMonster::GetAITurnSpeed()
{
	return 2.0f;
}

void ASZNormalMonster::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void ASZNormalMonster::AttackByAI(class UBTTask_Attack* Task)
{
	FGameplayAbilitySpec* AttackGASpec = ASC->FindAbilitySpecFromClass(USZGA_NormalAttack::StaticClass());
	if (!AttackGASpec)
	{
		UE_LOG(LogTemp, Log, TEXT("Error"));
		return; 
	}

	// 현재 공격 태스크에 전달 받은 태스크(BTTask_Attack) 몬스터 변수에 저장.
	CurrentAttackTask = Task;

	// 공격 어빌리티 실행.
	if (!AttackGASpec->IsActive())
	{
		ASC->TryActivateAbility(AttackGASpec->Handle);
	}

}

UAnimMontage* ASZNormalMonster::GetAttackAnimMontage()
{
	return AttackDataAsset->AttackData.AttackMontage;
}

int ASZNormalMonster::GetSectionCount()
{
	return AttackDataAsset->AttackData.SectionCount;
}


void ASZNormalMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ASC->InitAbilityActorInfo(NewController, this);

	ASC->ApplyGameplayEffectToSelf(
		MonsterInitGE.GetDefaultObject(),
		1.f,
		ASC->MakeEffectContext()
	);

	AttributeSet->InitHealth(AttributeSet->GetMaxHealth());

	FGameplayAbilitySpec AttackSkillSpec(USZGA_NormalAttack::StaticClass());
	ASC->GiveAbility(AttackSkillSpec);
}

void ASZNormalMonster::OnAttackHitNotify()
{
	UE_LOG(LogTemp, Log, TEXT("OnAttackHitNotify Ok"));
	if (CurrentAttackAbility)
	{
		ISZAttackAblilityInterface* Ability = Cast<ISZAttackAblilityInterface>(CurrentAttackAbility);
		if (Ability)
		{
			Ability->HitCheck();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("OnAttackHitNotify is nullptr"));
		}
	}
}

void ASZNormalMonster::OnSpawnFromPool_Implementation()
{
	// AI Run 시키기
	ASZNormalAIController* NormalController = Cast<ASZNormalAIController>(GetController());

	NormalController->RunAI();
	
	UE_LOG(LogTemp, Log, TEXT("Monster OnSpawnFromPool Call"));
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void ASZNormalMonster::OnReturnToPool_Implementation()
{
	// AI Stop 시키기
	ASZNormalAIController* NormalController = Cast<ASZNormalAIController>(GetController());

	NormalController->StopAI();

	UE_LOG(LogTemp, Log, TEXT("Monster OnReturnFromPool Call"));
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}






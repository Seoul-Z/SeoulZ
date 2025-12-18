// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "SZPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSEOULZ_API ASZPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void ShowPlayerHud();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUserWidget> PlayerHUD;
 
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMC", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> CurrentCharacterContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PlayerHUDClass;
};

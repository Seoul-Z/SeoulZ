// Fill out your copyright notice in the Description page of Project Settings.


#include "SZGameInstance.h"
#include "Kismet/GameplayStatics.h"

USZGameInstance::USZGameInstance()
{
	// @Todo: 처음은 로비 레벨이 불러와야함.
}

void USZGameInstance::OpenLevel(FName InSelectedMapName)
{
	// 맵이 선택되지 않았을 시 메세지 출력.
	if (InSelectedMapName.IsNone())
	{
		UE_LOG(LogTemp, Log, TEXT("Selected Map is none"));
	}
	// 맵이 선택되었을 때 레벨 실행 및 메세지 출력.
	else
	{
		UGameplayStatics::OpenLevel(this, InSelectedMapName);
		UE_LOG(LogTemp, Log, TEXT("Load Selected Map."));
	}
}

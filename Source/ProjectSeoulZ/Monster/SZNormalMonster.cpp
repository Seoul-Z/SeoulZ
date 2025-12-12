// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/SZNormalMonster.h"
#include "SZNormalMonster.h"
#include "AI/SZNormalAIController.h"

ASZNormalMonster::ASZNormalMonster()
{
	AIControllerClass = ASZNormalAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

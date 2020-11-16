// Copyright 2020 Team slow. All right reserved.

#include "Actor/SlowMobCharacterBase.h"
#include "Controller/SlowMobController.h"

ASlowMobCharacterBase::ASlowMobCharacterBase()
{
	AIControllerClass = ASlowMobController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASlowMobCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASlowMobCharacterBase::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}
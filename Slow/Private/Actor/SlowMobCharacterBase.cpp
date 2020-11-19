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

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
}

void ASlowMobCharacterBase::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}
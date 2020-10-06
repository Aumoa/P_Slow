// Copyright 2020 Aumoa.lib. All right reserved.

#include "Controller/SlowMobController.h"

ASlowMobController::ASlowMobController()
{
	PrimaryActorTick.bCanEverTick = true;

	bValidPossess = false;
}

void ASlowMobController::OnPossess(APawn* InTarget)
{
	Super::OnPossess(InTarget);

	MobCharacter = Cast<ASlowMobCharacterBase>(InTarget);
	bValidPossess = MobCharacter.IsValid();
}

void ASlowMobController::OnUnPossess()
{
	Super::OnUnPossess();

	MobCharacter = nullptr;
	bValidPossess = false;
}

bool ASlowMobController::IsValidPossess() const
{
	return bValidPossess;
}